#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "GL/glew.h"

// Compiles shader
GLuint compileShader(const GLenum& type, const char* source);

// Creates shader program
GLuint createShaderProgram();

#endif // SHADERS_HPP
