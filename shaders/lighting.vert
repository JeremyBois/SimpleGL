#version 330 core

// In
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;


uniform mat4 _modelM;
uniform mat4 _modelMInv;
uniform mat4 _viewM;
uniform mat4 _projectionM;
uniform mat3 _normalM;


// Out
out vec3 Normal;
out vec3 FragWorldPos;


void main()
{
    vec4 localPos = vec4(aPos, 1.0);

    // Vertex final position
    gl_Position = _projectionM * _viewM * _modelM * localPos;

    // Vertex position in world space for light calculations
    FragWorldPos = vec3(_modelM * localPos);

    // Normals must also be transformed with rotation and scale but not position
    // Also a non-uniform scale can make normals not normals anymore so
    // a Normal matrix must be used in place of ModelMatrix (_modelM)
    // http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/
    // normalM = transpose(_modelM⁻¹)
    Normal = normalize(_normalM * aNormal);
}
