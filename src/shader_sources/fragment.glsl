#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in mat3 TBN;

out vec4 FragColor;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D roughnessMap;
uniform sampler2D transparencyMap;

uniform bool useAlbedoMap;
uniform bool useNormalMap;
uniform bool useSpecularMap;
uniform bool useRoughnessMap;
uniform bool useTransparencyMap;

uniform vec3 viewPos;

struct SunLight
{
    vec3 color;
    float intensity;
    vec3 direction;
};

uniform SunLight sun;

void main()
{
    vec3 albedo       = useAlbedoMap       ? texture(albedoMap, TexCoords).rgb       : vec3(1.0);
    vec3 normalTex    = useNormalMap       ? texture(normalMap, TexCoords).rgb       : vec3(0.5, 0.5, 1.0);
    vec3 specular     = useSpecularMap     ? texture(specularMap, TexCoords).rgb     : vec3(1.0);
    vec3 roughness    = useRoughnessMap    ? texture(roughnessMap, TexCoords).rgb    : vec3(0.0);
    vec3 transparency = useTransparencyMap ? texture(transparencyMap, TexCoords).rgb : vec3(1.0);

    vec3 normal = normalize(TBN * (normalTex * 2.0 - 1.0));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 color = vec3(0.0);

    // --- Sun light ---
    vec3 lightDir = normalize(-sun.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mix(4.0, 128.0, 1.0 - roughness.r));
    color += sun.color * sun.intensity * (albedo * diff + specular * spec);

    FragColor = vec4(color, transparency.r);
}
