#ifndef MAIN_H
#define MAIN_H

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include "engine/Entity.h"

#include <string>
#include <map>
#include <vector>

#include "GL/glew.h"

extern GLuint shaderProgram;				   // Shader program
extern std::map<std::string, GLuint> textures; // Map of loaded textures. Keys represent paths, and values - texture ID
extern std::vector<Entity> ents;

int main(); // The entry point

GLuint compileShader(const GLenum& type, const char* source); // Compiles shader
GLuint createShaderProgram(); // Creates shader program

void useTexture(std::string path); // Loads texture (if needed), and binds it. If failed, uses just white color

#endif
