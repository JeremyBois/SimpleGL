#version 330 core

// Limit the number of light to compute
#define MAX_DIR_LIGHTS 2
#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4


// Container for a object color description
struct Material
{
    vec3 ambient;
    vec3 diffuse;
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

    vec3 color;
};

struct PointLight
{
    vec3 worldPosition;

    vec3 color;

    float constant;
    float linear;
    float quadratic;
};


// Container for a spot light
struct SpotLight
{
    vec3  worldPosition;
    vec3  worldDirection;

    vec3 color;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};


// Container for a directional light object
struct DirLight
{
    vec3 direction;

    vec3 color;
};




// In
in vec3 Normal;
in vec3 FragWorldPos;
in vec2 TexCoords;


// Directional lights
uniform DirLight   _dirLights_[MAX_DIR_LIGHTS];
uniform int        _DirLightCount_;

// Point lights
uniform PointLight _pointLights_[MAX_POINT_LIGHTS];
uniform int        _PointLightCount_;

// SpotLights
uniform SpotLight  _spotLights_[MAX_SPOT_LIGHTS];
uniform int        _SpotLightCount_;


uniform vec3 _viewWorldPos_;
uniform Material _objectMaterial_;
uniform float _time_;


// Out
out vec4 FragColor;


// Prototypes
vec3 ComputeDirLight(DirLight _dirLight, vec3 _normal, vec3 _viewDir);
vec3 ComputePointLight(PointLight _pointLight, vec3 _normal, vec3 _fragWorldPos, vec3 _viewDir);
vec3 ComputeSpotLight(SpotLight _spotLight, vec3 _normal, vec3 _fragWorldPos, vec3 _viewDir);



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

    // Compute spot lights influence
    int spotsMax = min(MAX_SPOT_LIGHTS, _SpotLightCount_);
    for(int i = 0; i < spotsMax; i++)
    {
        fragFinalColor += ComputeSpotLight(_spotLights_[i], Normal, FragWorldPos, viewDir);
    }

    // Compute emission
    fragFinalColor += _objectMaterial_.emission * texture(_objectMaterial_._emissionMap, TexCoords).rgb;


    // Gamma correction
    float gamma = 2.2;
    fragFinalColor = pow(fragFinalColor, vec3(1.0 / gamma));


    // Pass final color of pixel
    FragColor = vec4(fragFinalColor, 1.0f);
}



vec3 ComputeDirLight(DirLight _dirLight, vec3 _normal, vec3 _viewDir)
{
    // Compute ambient
    vec3 ambient = _dirLight.color * _objectMaterial_.ambient *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute diffuse using light direction reversed
    // ---> Direction to light
    vec3 lightDirection = normalize(-_dirLight.direction);
    float diffStrength = max(dot(_normal, lightDirection), 0.0);
    vec3 diffuse = _dirLight.color * _objectMaterial_.diffuse * diffStrength *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute specular (Blinh - Phong equations)
    vec3 halfVector = normalize(lightDirection + _viewDir);
    float specStrength = pow(max(dot(_normal, halfVector), 0.0), _objectMaterial_.shininess);
    // Specular material
    vec3 specular = _dirLight.color * _objectMaterial_.glossiness *
                    specStrength * vec3(texture(_objectMaterial_._specularMap, TexCoords));

    return (ambient + diffuse + specular);
}


vec3 ComputePointLight(PointLight _pointLight, vec3 _normal, vec3 _fragWorldPos, vec3 _viewDir)
{

    // Compute ambient
    vec3 ambient = _pointLight.color * _objectMaterial_.ambient *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute diffuse
    vec3 lightDirection = normalize(_pointLight.worldPosition - _fragWorldPos);
    float diffStrength = max(dot(_normal, lightDirection), 0.0);
    vec3 diffuse = _pointLight.color * _objectMaterial_.diffuse * diffStrength *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

    // Compute specular (Blinh - Phong equations)
    vec3 halfVector = normalize(lightDirection + _viewDir);
    float specStrength = pow(max(dot(_normal, halfVector), 0.0), _objectMaterial_.shininess);
    // Specular color comes from light not material
    vec3 specular = _pointLight.color * _objectMaterial_.glossiness *
                    specStrength * vec3(texture(_objectMaterial_._specularMap, TexCoords));

    // Attenuation
    float distance    = length(_pointLight.worldPosition - _fragWorldPos);
    float attenuation = 1.0 / (_pointLight.constant + _pointLight.linear * distance +
                               _pointLight.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;


    return (ambient + diffuse + specular);
}


vec3 ComputeSpotLight(SpotLight _spotLight, vec3 _normal, vec3 _fragWorldPos, vec3 _viewDir)
{
    // Attenuation
    float distance    = length(_spotLight.worldPosition - _fragWorldPos);
    float attenuation = 1.0 / (_spotLight.constant + _spotLight.linear * distance +
                               _spotLight.quadratic * (distance * distance));

    // Compute ambient
    vec3 ambient = _spotLight.color * _objectMaterial_.ambient *
                   vec3(texture(_objectMaterial_._diffuseMap, TexCoords));
    ambient *= attenuation;

    // Cos of angle used to check if frag inside the light area or not
    // Negate the angle to get direction toward the light
    vec3 lightDirection = normalize(_spotLight.worldPosition - _fragWorldPos);
    float cosTheta = dot(lightDirection, normalize(-_spotLight.worldDirection));

    // > because cos is close to 1.0 when angle is close to 0.0
    if(cosTheta > _spotLight.outerCutOff)
    {
        // Compute diffuse
        float diffStrength = max(dot(_normal, lightDirection), 0.0);
        vec3 diffuse = _spotLight.color * _objectMaterial_.diffuse * diffStrength *
                       vec3(texture(_objectMaterial_._diffuseMap, TexCoords));

        // Compute specular (Blinh - Phong equations)
        vec3 halfVector = normalize(lightDirection + _viewDir);
        float specStrength = pow(max(dot(_normal, halfVector), 0.0), _objectMaterial_.shininess);
        // Specular color comes from light not material
        vec3 specular = _spotLight.color * _objectMaterial_.glossiness *
                        specStrength * vec3(texture(_objectMaterial_._specularMap, TexCoords));

        float epsilon   = _spotLight.cutOff - _spotLight.outerCutOff;
        float intensity = clamp((cosTheta - _spotLight.outerCutOff) / epsilon, 0.0, 1.0);

        // Ambiant should not be influenced by intensity
        diffuse  *= (intensity * attenuation);
        specular *= (intensity * attenuation);


        return (ambient + diffuse + specular);
    }

    return ambient;
}
