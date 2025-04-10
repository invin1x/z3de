#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <GL/glew.h>
#include <string>

GLuint getTextureIdByName(const std::string& name);
bool loadTexture(const std::string& texture_path);

#endif // TEXTURES_HPP
