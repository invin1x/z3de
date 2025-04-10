#include "shaders.hpp"
#include "shader_sources.hpp"
#include "logging.hpp"
#include <vector>

// Compiles shader
GLuint compileShader(const GLenum& type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        log(ERROR, "Shader compilation error: \"" + std::string(infoLog) + "\".");
    }

    return shader;
}

// Creates shader program
GLuint createShaderProgram()
{
    std::vector<GLuint> shaders =
    {
        compileShader(GL_VERTEX_SHADER, SHADER_VERTEX_SOURCE),
        compileShader(GL_FRAGMENT_SHADER, SHADER_FRAGMENT_SOURCE)
    };

    GLuint shaderProgram = glCreateProgram();
    for (GLuint shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        log(ERROR, "Program linking error: \"" + std::string(infoLog) + "\".");
    }

    for (GLuint shader : shaders)
    {
        glDeleteShader(shader);
    }

    return shaderProgram;
}
