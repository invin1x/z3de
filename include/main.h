#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <map>

#include "GL/glew.h"

extern GLuint shaderProgram;				   // Shader program
extern std::map<std::string, GLuint> textures; // Map of loaded textures. Keys represent paths, and values - texture ID

int main(); // The entry point

GLuint compileShader(const GLenum& type, const char* source); // Compiles shader
GLuint createShaderProgram(); // Creates shader program

void useTexture(std::string path); // Loads texture (if needed), and binds it. If failed, uses just white color

#endif
