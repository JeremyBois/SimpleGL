#version 330 core

// Inputs vertex attributes and set location of that variable
layout (location = 0) in vec3 aPos;

// Pass color from program
layout (location = 1) in vec3 aColor;

// Pass color to fragment shader
out vec3 vertexColor;


void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
}
