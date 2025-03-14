#include "engine/Mesh.h"
#include "main.h"

#include <iostream>

// Constructor
Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<int>& indices, bool canBeDrawn, std::string tex)
    : vertices(vertices), uvs(uvs), indices(indices), canBeDrawn(canBeDrawn), tex(tex) {
    // Init mesh (VAO, VBO, EBO)
    std::vector<float> vertexData;
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertexData.push_back(vertices[i].x);
        vertexData.push_back(vertices[i].y);
        vertexData.push_back(vertices[i].z);
        vertexData.push_back(uvs[i].x);
        vertexData.push_back(uvs[i].y);
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

// Deconstructor
Mesh::~Mesh() {
    // Delete buffers and arrays
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// Draws the mesh
void Mesh::draw() {
    // Return, if mesh is not drawable
    if (!canBeDrawn)
        return;

    useTexture(tex);        // Use texture
    glBindVertexArray(VAO); // Bind VAO
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // Draw the binded VAO
    glBindVertexArray(0);   // Unbind VAO
}
