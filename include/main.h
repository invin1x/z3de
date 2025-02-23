#ifndef MAIN_H
#define MAIN_H

#include "GL/glew.h"

int main(); // The entry point

GLuint compileShader(const GLenum& type, const char* source); // Compiles shader
GLuint createShaderProgram(); // Creates shader program

#endif
