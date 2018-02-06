#version 330 core

out vec4 FragColor;
in vec3 vertexColor;

void main()
{
    // Color from vertex
    FragColor = vec4(vertexColor.xyz, 1.0f);
}
