#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D tex0;

out vec4 FragColor;

void main()
{
    vec4 t0 = texture2D(tex0, texCoord);

    // Multiplication
    FragColor = t0 * vertexColor;
}
