#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "GL/glew.h"
#include "glm.hpp"

struct Mesh {
private:
    std::vector<glm::vec3> vertices; // List of mesh vertices
    std::vector<glm::vec2> uvs;      // List of mesh texture coordinates
    std::vector<int> indices;        // Polygons vertices indices

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
public:
    bool canBeDrawn;
    std::string tex; // Path to texture

    Mesh(const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec2>& uvs,
        const std::vector<int>& indices,
        bool canBeDrawn = false,
        std::string tex = nullptr
    ); // Constructor
    ~Mesh(); // Deconstructor

    void draw(); // Draws the mesh
};

#endif // MESH_H
