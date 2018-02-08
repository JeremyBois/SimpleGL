#version 330 core

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;


// Out
out vec3 vertexColor;
out vec2 texCoord;

void main()
{
    // Vertex position
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    // To pixel shader
    vertexColor = aColor;
    texCoord = aTexCoord;
}
