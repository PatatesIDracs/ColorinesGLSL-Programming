#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;


out Data
{
    vec2 texCoords;
} VSOut;


void main(void)
{
    VSOut.texCoords = uv;

    gl_Position = vec4(position, 1);
}
