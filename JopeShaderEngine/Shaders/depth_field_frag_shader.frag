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
        outColor = vec4(0,1,1,1);

        if(depth < nearVision )
             outColor = vec4(0,0,1,1);
    }
    else if (depth > farFalloff)
    {
        outColor = vec4(1,1,0,1);

        if(depth > farVision)
            outColor = vec4(0,1,0,1);
    }
    else
    {
        outColor = vec4(1,0,1,1);
        //outColor = texture2D(lightTexture, FSIn.texCoords);
    }

}
