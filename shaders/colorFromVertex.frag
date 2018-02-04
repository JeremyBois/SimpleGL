#version 330 core
out vec4 FragColor;

in vec3 vertexColor;

void main()
{
    // Blue
    FragColor = vec4(vertexColor, 1.0f);
}
