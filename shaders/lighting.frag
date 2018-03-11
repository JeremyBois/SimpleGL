#version 330 core

// In
in vec3 Normal;
in vec3 FragWorldPos;


uniform vec3 viewWorldPos;
uniform vec3 lightWorldPos;
uniform vec3 lightColor;
uniform vec3 lightSpecularColor;
uniform vec3 objectColor;


// Out
out vec4 FragColor;


// Lighting calculation is done in world coordinates

void main()
{
    // Compute ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Compute diffuse
    vec3 lightDir = normalize(lightWorldPos - FragWorldPos);
    float diffStrength = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diffStrength * lightColor;

    // Compute specular
    float specularStrength = 0.5;
    int shininess = 32;
    vec3 viewDir = normalize(viewWorldPos - FragWorldPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightSpecularColor;

    vec3 finalColor = specular + (ambient + diffuse) * objectColor;
    FragColor = vec4(finalColor, 1.0f);
}
