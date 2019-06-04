#version 330

in Data
{
    vec2 texCoords;
} FSIn;

out vec4 outColor;

uniform sampler2D lightTexture;
uniform sampler2D bluredTexture;
uniform sampler2D depthTexture;

const float farVision = 0.92;
const float nearVision = 0.83;

const float farFalloff = 0.9;
const float nearFalloff = 0.86;

void main(void)
{

    float depth = texture2D(depthTexture, FSIn.texCoords).r;
    //depth = ((2.0 * nearVision) / (farVision + nearVision - (2.0 * depth - 1.0) * (farVision - nearVision)));

    if(depth < nearFalloff)
    {
        vec4 blured = texture2D(bluredTexture, FSIn.texCoords);
        vec4 light = texture2D(lightTexture, FSIn.texCoords);
        //blured = vec4(0,1,1,1);
        float ratio = (nearFalloff - depth) /(nearFalloff - nearVision);
        outColor = mix(light, blured, ratio);
        //outColor = vec4(0,1,1,1);
        if(depth < nearVision )
             outColor = texture2D(bluredTexture, FSIn.texCoords);
    }
    else if (depth > farFalloff)
    {
        vec4 blured = texture2D(bluredTexture, FSIn.texCoords);
        vec4 light = texture2D(lightTexture, FSIn.texCoords);
        float ratio = (farVision - depth) /(farVision - farFalloff);
        //blured = vec4(1,1,0,1);
        outColor = mix(blured, light, ratio);
        //outColor = vec4(1,1,0,1);
        if(depth > farVision)
            outColor = texture2D(bluredTexture, FSIn.texCoords);
    }
    else
    {
        outColor = texture2D(lightTexture, FSIn.texCoords);
    }

}
