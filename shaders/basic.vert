#version 330 core

// Inputs vertex attributes and set location of that variable
layout (location = 0) in vec3 aPos;


void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
