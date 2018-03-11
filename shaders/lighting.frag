#version 330 core

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


// In
in vec3 Normal;
in vec3 FragWorldPos;
in vec2 TexCoords;


uniform vec3 viewWorldPos;
uniform Light    light;
uniform Material objectMaterial;


// Out
out vec4 FragColor;


// Lighting calculation is done in world coordinates
void main()
{
    // Compute ambient
    vec3 ambient = light.ambient * objectMaterial.diffuse *
                   vec3(texture(objectMaterial._diffuseMap, TexCoords));

    // Compute diffuse
    vec3 lightDir = normalize(light.worldPosition - FragWorldPos);
    float diffStrength = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diffStrength * objectMaterial.diffuse *
                   vec3(texture(objectMaterial._diffuseMap, TexCoords));

    // // Compute specular (Phong equations)
    // vec3 viewDir = normalize(viewWorldPos - FragWorldPos);
    // vec3 reflectDir = reflect(-lightDir, Normal);
    // float specStrength = pow(max(dot(viewDir, reflectDir), 0.0), objectMaterial.shininess);
    // vec3 specular = objectMaterial.glossiness * (specStrength * objectMaterial.specular) * light.specular;

    // Compute specular (Blinh - Phong equations)
    vec3 viewDir = normalize(viewWorldPos - FragWorldPos);
    vec3 halfVector = normalize(lightDir + viewDir);
    float specStrength = pow(max(dot(Normal, halfVector), 0.0), objectMaterial.shininess);
    // Specular comes from light color not material
    vec3 specular = light.specular * objectMaterial.glossiness * specStrength *
                    vec3(texture(objectMaterial._specularMap, TexCoords));


    // Compute emission
    vec3 emission = objectMaterial.emission * texture(objectMaterial._emissionMap, TexCoords).rgb;

    vec3 finalColor = ambient + diffuse + specular + emission;
    FragColor = vec4(finalColor, 1.0f);
}
