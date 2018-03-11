#version 330 core

// Container for a object color description
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float glossiness;
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


uniform vec3 viewWorldPos;
uniform Light    light;
uniform Material objectMaterial;


// Out
out vec4 FragColor;


// Lighting calculation is done in world coordinates
void main()
{
    // Compute ambient
    vec3 ambient = objectMaterial.ambient * light.ambient;

    // Compute diffuse
    vec3 lightDir = normalize(light.worldPosition - FragWorldPos);
    float diffStrength = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = (diffStrength * objectMaterial.diffuse) * light.diffuse;

    // // Compute specular (Phong equations)
    // vec3 viewDir = normalize(viewWorldPos - FragWorldPos);
    // vec3 reflectDir = reflect(-lightDir, Normal);
    // float specStrength = pow(max(dot(viewDir, reflectDir), 0.0), objectMaterial.shininess);
    // vec3 specular = objectMaterial.glossiness * (specStrength * objectMaterial.specular) * light.specular;

    // Compute specular (Blinh - Phong equations)
    vec3 viewDir = normalize(viewWorldPos - FragWorldPos);
    vec3 halfVector = normalize(lightDir + viewDir);
    float specStrength = pow(max(dot(Normal, halfVector), 0.0), objectMaterial.shininess);
    vec3 specular = objectMaterial.glossiness * (specStrength * objectMaterial.specular) * light.specular;

    vec3 finalColor = ambient + diffuse + specular;
    FragColor = vec4(finalColor, 1.0f);
}
