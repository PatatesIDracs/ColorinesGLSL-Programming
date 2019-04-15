#version 330

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
} FSIn;

out vec4 outColor;

void main(void)
{
    vec3 L = -normalize(FSIn.positionViewspace);
    vec3 N = normalize(FSIn.normalViewspace);

    vec3 albedo = vec3(1.0);
    float kD = max(0.0, dot(L,N));
    outColor.rgb = albedo*kD;
    outColor.a = 1.0;

    outColor.rgb = pow(outColor.rgb, vec3(1.0/2.4));
}
