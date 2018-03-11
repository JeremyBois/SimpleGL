#version 330 core

// In
layout (location = 0) in vec3 aPos;

uniform mat4 _modelM;
uniform mat4 _viewM;
uniform mat4 _projectionM;

void main()
{
    // Vertex position
    gl_Position = _projectionM * _viewM * _modelM * vec4(aPos, 1.0);
}
