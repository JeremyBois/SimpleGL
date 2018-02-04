#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;

void main()
{
    // Color from main program on CPU
    FragColor = ourColor;
}
