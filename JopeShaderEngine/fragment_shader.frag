#version 330

layout(location = 0)out vec4 outColor;

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec2 textCoord;
} FSIn;

uniform vec4 albedo;
uniform vec4 specular;
uniform float smoothness;

uniform sampler2D albedoTexture;

void main(void)
{
    outColor = texture2D(albedoTexture, FSIn.textCoord);

    //outColor.rgb = pow(outColor.rgb, vec3(1.0/2.4));
}
