#ifndef SHADER_SOURCES_HPP
#define SHADER_SOURCES_HPP

// This header is being generated automaticly on build!!!
// If you want to edit shaders, edit "src/shader_sources/<your_shader>.glsl"

const char* SHADER_VERTEX_SOURCE = R"(#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;

out vec2 TexCoords;
out vec3 FragPos;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 T = normalize(mat3(model) * aTangent);
    vec3 N = normalize(mat3(model) * aNormal);
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);

    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* SHADER_FRAGMENT_SOURCE = R"(#version 330 core

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
)";


#endif // SHADER_SOURCES_HPP
