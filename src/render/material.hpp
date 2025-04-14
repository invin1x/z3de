#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <GL/glew.h>

struct Material
{
    std::string albedo_map;
    std::string normal_map;
    std::string specular_map;
    std::string roughness_map;
    std::string transparency_map;
    bool lightning;

    // Constructor
    Material
    (
        const std::string& albedo_map = "",
        const std::string& normal_map = "",
        const std::string& specular_map = "",
        const std::string& roughness_map = "",
        const std::string& transparency_map = "",
        bool lightning = true
    )
      : albedo_map(albedo_map),
        normal_map(normal_map),
        specular_map(specular_map),
        roughness_map(roughness_map),
        transparency_map(transparency_map),
        lightning(lightning) {}
};

GLuint getTextureIdByName(const std::string& name);
bool loadTexture(const std::string& texture_path);

#endif // MATERIAL_HPP
