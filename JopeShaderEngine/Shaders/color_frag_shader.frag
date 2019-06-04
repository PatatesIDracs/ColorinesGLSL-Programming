#version 330

layout(location = 0)out vec4 outColor;
layout(location = 1)out vec4 outNormal;
layout(location = 2)out vec4 outPosition;


in Data
{
    vec3 normalLocalspace;
    vec2 textCoord;
    vec3 positionWorld;
} FSIn;

uniform mat4 worldViewMatrix;

uniform sampler2D albedoTexture;

uniform bool hasTexture;

void main(void)
{
    if(hasTexture)
        outColor = vec4(texture2D(albedoTexture, FSIn.textCoord).xyz,1);
    else outColor = vec4(1, 0, 0.5, 1);

    outNormal = vec4(FSIn.normalLocalspace,1);
    outPosition = vec4(FSIn.positionWorld, 1);

}
