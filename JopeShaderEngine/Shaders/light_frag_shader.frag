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

const vec3 light = vec3(0, 0, 10);

void main(void)
{

    vec3 FragPos = texture2D(posTex, FSIn.texCoord).rgb;
    vec3 Normal = texture2D(normalTex, FSIn.texCoord).rgb;
    vec3 Color = texture2D(colorTex, FSIn.texCoord).rgb;

    vec3 lighting = Color * 0.1;

    vec3 lightDir = normalize(light - FragPos);
    //vec3 lightDir = vec3(0.0f,0.0f,1.0f);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Color * vec3(1,1,1);
    lighting += diffuse;

    //outColor = vec4(FSIn.texCoord.x,FSIn.texCoord.y, 0, 1);

    outLight = vec4(lighting, 1.0);
    //outLight = vec4(1,0,1,1);
}
