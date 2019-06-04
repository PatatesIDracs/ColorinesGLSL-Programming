#version 330 core

in Data
{
    vec3 color;
    vec2 texCoord;
} FSIn;

out vec4 outLight;

uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D posTex;

const vec3 lightPos = vec3(5, 5, 5);

void main(void)
{

    vec3 FragPos = texture2D(posTex, FSIn.texCoord).rgb;
    vec3 Normal = texture2D(normalTex, FSIn.texCoord).rgb;
    vec3 Color = texture2D(colorTex, FSIn.texCoord).rgb;

    vec3 lighting = Color * 0.1;

    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Color * vec3(1,1,1);
    lighting += diffuse;


    outLight = vec4(lighting, 1.0);
}
