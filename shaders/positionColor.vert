#version 330 core
// Define version and that we use core functionality

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 _modelM;
uniform mat4 _viewM;
uniform mat4 _projectionM;
// uniform mat4 _modelMInv;


// Out
out vec4 vertexColor;

void main()
{
    gl_Position = _projectionM * _viewM * _modelM * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = gl_Position;
}
