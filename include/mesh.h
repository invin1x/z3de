#ifndef MESH_H
#define MESH_H

#include <vector>
#include "GL/glew.h"
#include "glm.hpp"

struct mesh {
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
public:
    std::vector<glm::vec3> vertices; // List of mesh vertices
    std::vector<glm::vec2> uvs;      // List of mesh texture coordinates
    std::vector<int> indices;        // Polygons vertices indices
    GLuint textureID;                // Texture ID

    mesh(const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec2>& uvs,
        const std::vector<int>& indices,
        const char* texturePath
    ); // Constructor
    ~mesh(); // Deconstructor

    void draw(); // Method to draw the mesh
};

#endif // MESH_H
