#ifndef SUNLIGHT_HPP
#define SUNLIGHT_HPP

#include "glm.hpp"

struct SunLight
{
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;

    SunLight
    (
        const glm::vec3& direction,
        const glm::vec3& color,
        float intensity
    )
      : direction(direction),
        color(color),
        intensity(intensity) {}
};

#endif // SUNLIGHT_HPP
