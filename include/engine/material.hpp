#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

struct Material
{
    std::string albedo_map;
    std::string normal_map;
    std::string specular_map;
    std::string roughness_map;
    std::string transparency_map;

    // Constructor
    Material
    (
        const std::string& albedo_map = "",
        const std::string& normal_map = "",
        const std::string& specular_map = "",
        const std::string& roughness_map = "",
        const std::string& transparency_map = ""
    )
      : albedo_map(albedo_map),
        normal_map(normal_map),
        specular_map(specular_map),
        roughness_map(roughness_map),
        transparency_map(transparency_map) {}
};

#endif // MATERIAL_HPP
