#include "material.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "logging.hpp"
#include <unordered_map>

namespace
{
    std::unordered_map<std::string, GLuint> textures;
}

GLuint getTextureIdByName(const std::string& name)
{
    auto it = textures.find(name);
    if (it != textures.end())
        return it->second;

    return -1;
}

bool loadTexture(const std::string& texture_path)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        log(ERROR, "Failed to load texture.");
        return false;
    }
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    textures[texture_path] = texId;
    log(INFO, "Texture successfuly loaded.");

    stbi_image_free(data);
    return true;
}
