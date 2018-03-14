#version 330 core

// In
layout (location = 0) in vec3 aPos;

uniform mat4 _modelM_;
uniform mat4 _viewM_;
uniform mat4 _projectionM_;

void main()
{
    // Vertex position
    gl_Position = _projectionM_ * _viewM_ * _modelM_ * vec4(aPos, 1.0);
}
