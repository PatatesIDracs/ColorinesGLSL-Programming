#version 330

in Data
{
    vec2 texCoords;
} FSIn;

out vec4 outColor;

uniform vec2 texCoordsInc;

uniform sampler2D colorTexture;

void main(void)
{
    float weights[11];
    weights[0] = 0.035822;
    weights[1] = 0.05879;
    weights[2] = 0.086425;
    weights[3] = 0.113806;
    weights[4] = 0.13424;
    weights[5] = 0.141836;
    weights[6] = 0.13424;
    weights[7] = 0.113806;
    weights[8] = 0.086425;
    weights[9] = 0.05879;
    weights[10] = 0.035822;

    vec3 blurredColor = vec3(0.0);
    vec2 uv = FSIn.texCoords - texCoordsInc * 5.0;

    float sumWeights = 0.0f;
    for(int i = 0; i < 11; ++i)
    {
        blurredColor += texture2D(colorTexture, uv).rgb * weights[i];
        sumWeights += weights[i];
        uv += texCoordsInc;
    }
    blurredColor /= sumWeights;
    outColor.rgb = blurredColor;
    outColor.a = 1.0;
}
