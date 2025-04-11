#ifndef LIGHTS_HPP
#define LIGHTS_HPP

#include "glm.hpp"

struct Light
{
    glm::vec3 position;
    glm::vec3 direction;
    float angle;
    glm::vec3 color;
    float intensity;

    Light
    (
        const glm::vec3& position,
        const glm::vec3& direction,
        float angle,
        const glm::vec3& color,
        float intensity
    )
      : position(position),
        direction(direction),
        angle(angle),
        color(color),
        intensity(intensity) {}
};

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

#endif // LIGHTS_HPP
