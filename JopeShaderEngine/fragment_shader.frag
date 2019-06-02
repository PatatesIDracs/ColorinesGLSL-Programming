#version 330

layout(location = 0)out vec4 outColor;

in Data
{
    vec3 normalLocalspace;
    vec2 textCoord;
    vec3 positionViewspace;
} FSIn;

uniform mat4 worldViewMatrix;

uniform sampler2D albedoTexture;

void main(void)
{
    float ambientTerm = 0.05f;

    vec4 albedo;
    vec4 ambient;
    vec3 lightDir = vec3(0.0f,0.0f,1.0f);
    vec3 lightColor = vec3(1.0f,1.0f,1.0f);


    albedo = texture2D(albedoTexture, FSIn.textCoord);

    ambient = albedo * ambientTerm;
    ambient.a = 1.0f;

    outColor.rgb = ambient.rgb + albedo.rgb * dot(lightDir,FSIn.normalLocalspace) * lightColor;
    outColor.a = 1.0f;

}
