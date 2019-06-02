#version 330 core

in Data
{
    vec3 color;
    vec2 texCoord;
} FSIn;

out vec4 outColor;

uniform sampler2D colorTexture;

void main(void)
{
    //outColor = vec4(FSIn.texCoord.x,FSIn.texCoord.y, 0, 1);
    outColor = texture2D(colorTexture, FSIn.texCoord);
}
