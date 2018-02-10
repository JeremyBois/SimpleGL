#version 330 core

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D tex0;

out vec4 FragColor;

void main()
{
    vec4 t0 = texture2D(tex0, texCoord);
    vec4 t1 = vec4(vertexColor.xyz, t0.a);

    // Multiplication
    FragColor = t0 * t1;
}
