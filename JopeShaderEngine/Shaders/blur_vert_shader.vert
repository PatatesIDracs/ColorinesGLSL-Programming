#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out Data
{
    vec2 texCoords;
} VSOut;


void main(void)
{
    VSOut.texCoords = uv;

    gl_Position = vec4(position,0 , 1);
}
