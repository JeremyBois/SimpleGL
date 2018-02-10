#version 330 core

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float uvScale;

out vec4 FragColor;

void main()
{
    vec4 color = vec4(vertexColor.xyz, 1.0);

    vec4 t0 = texture2D(tex0, texCoord * uvScale);
    vec4 t1 = texture2D(tex1, texCoord);

    // Multiplication then alpha blending
    FragColor = mix(color * t0, t1, 0.006 * t1.a);
}
