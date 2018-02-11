#version 330 core
// Define version and that we use core functionality

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

// Out
out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
}
