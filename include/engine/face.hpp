#ifndef FACE_HPP
#define FACE_HPP

#include <vector>
#include "GL/glew.h"
#include "glm.hpp"
#include "engine/material.hpp"

struct Face
{
private:
    GLuint VAO, VBO, EBO;
public:
    std::vector<glm::vec3> verts;
    Material mat;
    std::vector<glm::vec2> uvs;

    Face
    (
        const std::vector<glm::vec3>& verts,
        const Material& mat,
        const std::vector<glm::vec2>& uvs
    );

    ~Face();

    void draw();
};

#endif // FACE_HPP
