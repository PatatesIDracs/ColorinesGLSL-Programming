#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 textCoords;
layout(location=3) in vec3 tangent;
layout(location=4) in vec3 bitangent;

uniform mat4 projectionMatrix;
uniform mat4 worldViewMatrix;

out Data
{
    vec3 normalLocalspace;
    vec2 textCoord;
    vec3 positionWorld;
} VSOut;

void main(void)
{
    VSOut.textCoord = textCoords;

    VSOut.normalLocalspace = (projectionMatrix*vec4(normal,0)).xyz;

    gl_Position = projectionMatrix*vec4((worldViewMatrix*vec4(position, 1)).xyz, 1.0);

    VSOut.positionWorld = (projectionMatrix*vec4(position, 1)).xyz;
}
