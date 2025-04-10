#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

struct Material
{
    std::string albedo_map;
    std::string normal_map;

    // Constructor
    Material
    (
        const std::string& albedo_map = "",
        const std::string& normal_map = ""
    ) : albedo_map(albedo_map), normal_map(normal_map) {}
};

#endif // MATERIAL_HPP
