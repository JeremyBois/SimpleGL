#version 330 core

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 _modelM;
uniform mat4 _viewM;
uniform mat4 _projectionM;
// uniform mat4 _modelMInv;

// Out
out vec4 vertexColor;
out vec2 texCoord;

void main()
{
    // Vertex position
    gl_Position = _projectionM * _viewM * _modelM * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    // To pixel shader
    vertexColor = aColor;
    texCoord = aTexCoord;
}
