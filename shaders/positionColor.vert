#version 330 core
// Define version and that we use core functionality

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 _modelM_;
uniform mat4 _viewM_;
uniform mat4 _projectionM_;


// Out
out vec4 vertexColor;

void main()
{
    gl_Position = _projectionM_ * _viewM_ * _modelM_ * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = gl_Position;
}
