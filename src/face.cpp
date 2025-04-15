#include "face.hpp"
#include "glm.hpp"

Face::Face
(
    const std::vector<glm::vec3>& verts,
    const Material& mat,
    const std::vector<glm::vec2>& uvs
) : verts(verts), mat(mat), uvs(uvs)
{
    glm::vec3 normal = glm::normalize(glm::cross(verts[1] - verts[0], verts[2] - verts[0]));

    glm::vec3 edge1 = verts[1] - verts[0];
    glm::vec3 edge2 = verts[2] - verts[0];
    glm::vec2 deltaUV1 = uvs[1] - uvs[0];
    glm::vec2 deltaUV2 = uvs[2] - uvs[0];

    glm::vec3 tangent =  glm::normalize
    (
        glm::vec3
        (
            deltaUV2.y * edge1.x - deltaUV1.y * edge2.x,
            deltaUV2.y * edge1.y - deltaUV1.y * edge2.y,
            deltaUV2.y * edge1.z - deltaUV1.y * edge2.z
        )
    );

    // Init VAO, VBO, EBO
    std::vector<float> vertexData;
    for (size_t i = 0; i < verts.size(); ++i)
    {
        vertexData.push_back(verts[i].x);
        vertexData.push_back(verts[i].y);
        vertexData.push_back(verts[i].z);
        vertexData.push_back(uvs[i].x);
        vertexData.push_back(uvs[i].y);
        vertexData.push_back(normal.x);
        vertexData.push_back(normal.y);
        vertexData.push_back(normal.z);
        vertexData.push_back(tangent.x);
        vertexData.push_back(tangent.y);
        vertexData.push_back(tangent.z);
    }
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

// Deconstructor
Face::~Face()
{
    // Delete buffers and arrays
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Face::draw(const GLuint& shaderProgram)
{
    glUniform1i(glGetUniformLocation(shaderProgram, "useAlbedoMap"),       mat.albedo_map != "");
    glUniform1i(glGetUniformLocation(shaderProgram, "useNormalMap"),       mat.normal_map != "");
    glUniform1i(glGetUniformLocation(shaderProgram, "useSpecularMap"),     mat.specular_map != "");
    glUniform1i(glGetUniformLocation(shaderProgram, "useRoughnessMap"),    mat.roughness_map != "");
    glUniform1i(glGetUniformLocation(shaderProgram, "useTransparencyMap"), mat.transparency_map != "");
    glUniform1i(glGetUniformLocation(shaderProgram, "lightning"),          mat.lightning);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, getTextureIdByName(mat.albedo_map));

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, getTextureIdByName(mat.normal_map));

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, getTextureIdByName(mat.specular_map));

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, getTextureIdByName(mat.roughness_map));

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, getTextureIdByName(mat.transparency_map));

    glBindVertexArray(VAO); // Bind VAO
    glDrawArrays(GL_POLYGON, 0, verts.size()); // Draw the binded VAO
    glBindVertexArray(0);   // Unbind VAO
}
