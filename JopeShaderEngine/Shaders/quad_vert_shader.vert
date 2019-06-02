#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;


out Data
{
    vec3 color;
    vec2 texCoord;
} VSOut;

uniform sampler2D tex;
uniform sampler2D normalMap;

void main(void)
{
    gl_Position = vec4(position, 1);
    VSOut.texCoord = uv;
}
