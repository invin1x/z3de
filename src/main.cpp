#include "main.h"
#include "shaders/vertex.h"
#include "shaders/fragment.h"
#include "engine/Mesh.h"
#include "engine/Camera.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "stb_image.h"

GLuint shaderProgram;                   // Shader program
std::map<std::string, GLuint> textures; // Map of loaded textures. Keys represent paths, and values - texture ID


// The entry point
int main() {
    // Init GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "z3de", nullptr, nullptr); // Create window
    glfwMakeContextCurrent(window);

    // Init OpenGL
    glewInit();
    glEnable(GL_DEPTH_TEST);                      // Enable depth test for 3D
    shaderProgram = createShaderProgram(); // Create shader program
    glUseProgram(shaderProgram);                  // Use this shader program

    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // Link texture sample to texture unit

    std::vector<Mesh> meshes; // List of meshes to draw

    Camera camera(
        glm::vec3(-3, 3, 3),
        glm::vec3(glm::radians(45.0f),
        glm::radians(-45.0f),
        glm::radians(0.0f)),
        glm::radians(90.0f),
        16.0f / 9
    ); // Camera relative to which meshes are being drawed

    // Add test cube to the list of meshes
    meshes.emplace_back(
        std::vector<glm::vec3> {
            {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f },
            { -0.5f, -0.5f,  0.5f }, { 0.5f, -0.5f,  0.5f }, { 0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f },
            { -0.5f, -0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f },
            { 0.5f, -0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f,  0.5f }, { 0.5f, -0.5f,  0.5f },
            { -0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f },
            { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f }
        },
        std::vector<glm::vec2> {
            {0.0f, 0.0f}, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
            { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
            { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
            { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
            { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
            { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }
        },
        std::vector<int> {
        0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
        },
        true,
        "test.png"
    );

    //
    // MAIN GAME LOOP
    //
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffer

        float speed = 0.005f;
        float sens = 0.0025f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.pos += camera.getForward() * speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.pos += camera.getLeft() * speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.pos -= camera.getForward() * speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.pos -= camera.getLeft() * speed;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.pos += glm::vec3(0, 0, 1) * speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.pos -= glm::vec3(0, 0, 1) * speed;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            camera.ang += glm::vec3(-sens, 0, 0);
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.ang += glm::vec3(sens, 0, 0);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            camera.ang += glm::vec3(0, sens, 0);
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            camera.ang += glm::vec3(0, -sens, 0);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.ang += glm::vec3(0, 0, -sens);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera.ang += glm::vec3(0, 0, sens);

        // Apply transform matrices
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, value_ptr(camera.getView()));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, value_ptr(camera.getProj()));

        // Draw every mesh
        for (Mesh& mesh : meshes) {
            mesh.draw();
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //
    // END OF MAIN GAME LOOP
    //

    // Unload textures
    for (const auto& texture : textures)
        glDeleteTextures(1, &texture.second);

    glfwTerminate(); // Unload GLFW
    return 0;        // GG
};

// Compiles shader
GLuint compileShader(const GLenum& type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader compilation error: " << infoLog << std::endl;
    }

    return shader;
}

// Creates shader program
GLuint createShaderProgram() {
    std::vector<GLuint> shaders = {
        compileShader(GL_VERTEX_SHADER, VERTEX_SHADER_SRC),
        compileShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SRC)
    };

    GLuint shaderProgram = glCreateProgram();
    for (GLuint shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Program linking error: " << infoLog << std::endl;
    }

    for (GLuint shader : shaders) {
        glDeleteShader(shader);
    }

    return shaderProgram;
}

// Loads texture (if needed), and binds it. If failed, uses just white color
void useTexture(std::string path) {
    if (textures.find(path) == textures.end()) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
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
            textures[path] = texId;
        }
        else {
            std::cout << "Failed to load texture: " << path << std::endl;
            glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            return;
        }
        stbi_image_free(data);
    }
    glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[path]);
}
