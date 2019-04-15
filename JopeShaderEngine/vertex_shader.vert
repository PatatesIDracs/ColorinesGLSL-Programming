#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 textCoords;

uniform mat4 projectionMatrix;
uniform mat4 worldViewMatrix;

out Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
} VSOut;

void main(void)
{
    VSOut.positionViewspace = (worldViewMatrix*vec4(position, 1)).xyz;
    VSOut.normalViewspace = (worldViewMatrix*vec4(normal,0)).xyz;

    gl_Position = projectionMatrix*vec4(VSOut.positionViewspace, 1.0);
}
