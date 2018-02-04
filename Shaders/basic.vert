#version 330 core
// Define version and that we use core functionality

// Inputs vertex attributes and set location of that variable
layout (location = 0) in vec3 aPos;

// Specify a color output to the fragment shader
out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);  // Set a darkRed color
}
