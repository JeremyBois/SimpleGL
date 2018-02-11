#version 330 core
// Define version and that we use core functionality

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 ObjectToWorld;
// uniform mat4 WorldToObject;


// Out
out vec4 vertexColor;

void main()
{
    gl_Position = ObjectToWorld * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
}
