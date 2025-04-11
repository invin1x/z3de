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

uniform bool lightning;

uniform vec3 viewPos;

struct SunLight
{
    vec3 color;
    float intensity;
    vec3 direction;
};
struct Light {
    vec3 position;
    vec3 direction;
    float angle;
    vec3 color;
    float intensity;
};

uniform SunLight sun;

#define MAX_POINT_LIGHTS 8
uniform Light pointLights[MAX_POINT_LIGHTS];
uniform int numPointLights;

void main()
{
    vec3 albedo       = useAlbedoMap       ? texture(albedoMap, TexCoords).rgb       : vec3(1.0);

    if (lightning)
    {
        vec3 normalTex    = useNormalMap       ? texture(normalMap, TexCoords).rgb       : vec3(0.5, 0.5, 1.0);
        vec3 specular     = useSpecularMap     ? texture(specularMap, TexCoords).rgb     : vec3(0.5);
        vec3 roughness    = useRoughnessMap    ? texture(roughnessMap, TexCoords).rgb    : vec3(0.5);
        vec3 transparency = useTransparencyMap ? texture(transparencyMap, TexCoords).rgb : vec3(1.0);

        vec3 normal = normalize(TBN * (normalTex * 2.0 - 1.0));
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 color = vec3(0.0);

        // --- Sun light ---
        vec3 lightDir = normalize(-sun.direction);
        vec3 halfwayDir = normalize(lightDir + viewDir);

        // Diffuse
        float diff = max(dot(normal, lightDir), 0.1);

        // Specular (Blinn-Phong)
        float shininess = mix(4.0, 128.0, 1.0 - roughness.r);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);

        vec3 sunLight = albedo * diff + specular * spec;
        color += sun.color * sun.intensity * sunLight;

        // --- Point lights ---
        for (int i = 0; i < numPointLights; ++i)
        {
            Light light = pointLights[i];

            vec3 toLight = light.position - FragPos;
            float distance = length(toLight);
            vec3 lightDir = normalize(toLight);

            // Spotlight angle attenuation
            float angleCos = dot(lightDir, normalize(-light.direction));
            float angleAtten = 100.0;
            if (light.angle < 6.2814)
            {
                float halfAngle = light.angle * 0.5;
                angleAtten = clamp((angleCos - cos(halfAngle)) / (1.0 - cos(halfAngle)), 0.0, 1.0);
            }

            // Diffuse
            float diff = max(dot(normal, lightDir), 0.0);

            // Specular
            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), mix(4.0, 128.0, 1.0 - roughness.r));

            // Attenuation (basic inverse square)
            float attenuation = 1.0 / (distance * distance);

            vec3 lightColor = light.color * light.intensity * angleAtten * attenuation;
            color += lightColor * (albedo * diff + specular * spec);
        }
        color = pow(color, vec3(1.0/3.0));
        FragColor = vec4(color, transparency.r);
        return;
    }
    
    FragColor = vec4(albedo, 1.0);
}
