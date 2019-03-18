#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

struct Material
{
    sampler2D _diffuseMap0;
};
// To be populated by Material class
uniform Material _objectMaterial_;


out vec4 FragColor;




void main()
{
    vec4 t0 = texture2D(_objectMaterial_._diffuseMap0, texCoord);

    // Multiplication
    FragColor = t0 * vertexColor;

    // Gamma correction
    float gamma = 2.2;
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0 / gamma));
}
