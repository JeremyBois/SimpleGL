#version 330 core

// Limit the number of light to compute
#define MAX_POINT_LIGHTS 4
#define MAX_DIR_LIGHTS 2


// Container for a object color description
struct Material
{
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
    float glossiness;

    sampler2D _diffuseMap;
    sampler2D _specularMap;
    sampler2D _emissionMap;
};

// Container for a light object
struct Light
{
    vec3 worldPosition;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 worldPosition;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


// Container for a directional light object
struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


// In
in vec3 Normal;
in vec3 FragWorldPos;
in vec2 TexCoords;


// Directional + Point
uniform DirLight   _dirLights_[MAX_DIR_LIGHTS];
uniform PointLight _pointLights_[MAX_POINT_LIGHTS];
uniform int        _PointLightCount_;
uniform int        _DirLightCount_;

uniform vec3 _viewWorldPos_;
uniform Material _objectMaterial_;
uniform float _time_;


// Out
out vec4 FragColor;


// Prototypes
vec3 ComputeDirLight(DirLight _light, vec3 _normal, vec3 _viewDir);
vec3 ComputePointLight(PointLight _pointLight, vec3 _normal, vec3 _fragWorldPos, vec3 _viewDir);



// Lighting calculation is done in world coordinates
void main()
{
    // Compute camera direction
    vec3 viewDir = normalize(_viewWorldPos_ - FragWorldPos);

    vec3 fragFinalColor = vec3(0.0f, 0.0, 0.0);

    // Compute directional lights influence
    int dirMax = min(MAX_DIR_LIGHTS, _DirLightCount_);
    for(int i = 0; i < dirMax; i++)
    {
        fragFinalColor += ComputeDirLight(_dirLights_[i], Normal, viewDir);;
    }

    // Compute point lights influence
    int pointsMax = min(MAX_POINT_LIGHTS, _PointLightCount_);
    for(int i = 0; i < pointsMax; i++)
    {
        fragFinalColor += ComputePointLight(_pointLights_[i], Normal, FragWorldPos, viewDir);
    }

    // Compute emission
    fragFinalColor += _objectMaterial_.emission * texture(_objectMaterial_._emissionMap, TexCoords).rgb;


    // Gamma correction
    float gamma = 2.2;
    fragFinalColor = pow(fragFinalColor, vec3(1.0 / gamma));


    // Pass final color of pixel
    FragColor = vec4(fragFinalColor, 1.0f);
}



vec3 ComputeDirLight(DirLight _light, vec3 _normal, vec3 _viewDir)
{
    // Compute ambient
    vec3 ambient = _light.ambient * _objectMaterial_.diffuse *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute diffuse using light direction reversed
    // ---> Direction to light
    vec3 lightDir = normalize(-_light.direction);
    float diffStrength = max(dot(_normal, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diffStrength * _objectMaterial_.diffuse *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute specular (Blinh - Phong equations)
    vec3 halfVector = normalize(lightDir + _viewDir);
    float specStrength = pow(max(dot(_normal, halfVector), 0.0), _objectMaterial_.shininess);
    // Specular comes from _light color not material
    vec3 specular = _light.specular * _objectMaterial_.glossiness * specStrength *
                    vec3(texture(_objectMaterial_._specularMap, TexCoords));

    return (ambient + diffuse + specular);
}


vec3 ComputePointLight(PointLight _pointLight, vec3 _normal, vec3 _fragWorldPos, vec3 _viewDir)
{

    // Compute ambient
    vec3 ambient = _pointLight.ambient * _objectMaterial_.diffuse *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute diffuse
    vec3 lightDir = normalize(_pointLight.worldPosition - _fragWorldPos);
    float diffStrength = max(dot(_normal, lightDir), 0.0);
    vec3 diffuse = _pointLight.diffuse * diffStrength * _objectMaterial_.diffuse *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute specular (Blinh - Phong equations)
    vec3 halfVector = normalize(lightDir + _viewDir);
    float specStrength = pow(max(dot(_normal, halfVector), 0.0), _objectMaterial_.shininess);
    // Specular comes from _pointLight color not material
    vec3 specular = _pointLight.specular * _objectMaterial_.glossiness * specStrength *
                    vec3(texture(_objectMaterial_._specularMap, TexCoords));

    // Attenuation
    float distance    = length(_pointLight.worldPosition - _fragWorldPos);
    float attenuation = 1.0 / (_pointLight.constant + _pointLight.linear * distance +
                               _pointLight.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;


    return (ambient + diffuse + specular);
}
