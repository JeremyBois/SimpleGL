#version 330 core
// Define version and that we use core functionality

// Inputs vertex attributes and set location of that variable
layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aColor;

// Specify a color output to the fragment shader
out vec3 vertexColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
}
