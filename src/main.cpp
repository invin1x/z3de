#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "logging.hpp"
#include "bindings.hpp"
#include "face.hpp"
#include "material.hpp"
#include "shaders.hpp"
#include "camera.hpp"
#include "light_structs/light.hpp"
#include "light_structs/sunlight.hpp"

bool console_visible = false;

float speed = 0.1f;
float sens = 0.05f;

bool is_moving_forward = false;
bool is_moving_back = false;
bool is_moving_left = false;
bool is_moving_right = false;
bool is_looking_up = false;
bool is_looking_down = false;
bool is_looking_left = false;
bool is_looking_right = false;

void keyCallback(
    GLFWwindow* window,
    int key, int scancode,
    int action,
    int mods)
{
    switch(action)
    {
        case GLFW_PRESS:
        {
            if (key == key_exit)
            {
                glfwSetWindowShouldClose(window, true);
                return;
            }
            else if (key == key_toggle_developer_console)
            {
                if (!console_visible)
                {
                    log(INFO, "Developer console shown.");
                    console_visible = true;
                }
                else
                {
                    log(INFO, "Developer console hidden.");
                    console_visible = false;
                }
                return;
            }

            else if (key == key_move_forward)
            {
                is_moving_forward = true;
                log(INFO, "+forward");
            }
            else if (key == key_move_back)
            {
                is_moving_back = true;
                log(INFO, "+back");
            }
            else if (key == key_move_left)
            {
                is_moving_left = true;
                log(INFO, "+left");
            }
            else if (key == key_move_right)
            {
                is_moving_right = true;
                log(INFO, "+right");
            }

            else if (key == key_look_up)
            {
                is_looking_up = true;
                log(INFO, "+lookup");
            }
            else if (key == key_look_down)
            {
                is_looking_down = true;
                log(INFO, "+lookdown");
            }
            else if (key == key_look_left)
            {
                is_looking_left = true;
                log(INFO, "+lookleft");
            }
            else if (key == key_look_right)
            {
                is_looking_right = true;
                log(INFO, "+lookright");
            }
            break;
        }
        case GLFW_RELEASE:
        {
            if (key == key_move_forward)
            {
                is_moving_forward = false;
                log(INFO, "-forward");
            }
            else if (key == key_move_back)
            {
                is_moving_back = false;
                log(INFO, "-back");
            }
            else if (key == key_move_left)
            {
                is_moving_left = false;
                log(INFO, "-left");
            }
            else if (key == key_move_right)
            {
                is_moving_right = false;
                log(INFO, "-right");
            }

            else if (key == key_look_up)
            {
                is_looking_up = false;
                log(INFO, "-lookup");
            }
            else if (key == key_look_down)
            {
                is_looking_down = false;
                log(INFO, "-lookdown");
            }
            else if (key == key_look_left)
            {
                is_looking_left = false;
                log(INFO, "-lookleft");
            }
            else if (key == key_look_right)
            {
                is_looking_right = false;
                log(INFO, "-lookright");
            }
            break;
        }
    }
}

// The entry point
int main()
{
    // Open log file to save logs
    openLogFile();

    log(INFO, "Starting...");

    // Initialize GLFW
    if(!glfwInit())
    {
        log(FATAL, "An error has occurred while initializing GLFW.");
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "z3de", nullptr, nullptr);
    if (!window)
    {
        log(FATAL, "An error has occurred while creating a window.");
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context of the window current
    glfwMakeContextCurrent(window);

    // Set key callback function
    glfwSetKeyCallback(window, keyCallback);

    // Initialize GLEW
    glewInit();

    // Initialize ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // ---- ---- ----

    glEnable(GL_DEPTH_TEST);                      // Enable depth test for 3D

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    GLuint shaderProgram = createShaderProgram(); // Create shader program
    glUseProgram(shaderProgram);                  // Use this shader program

    glUniform1i(glGetUniformLocation(shaderProgram, "albedoMap"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "normalMap"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "specularMap"), 2);
    glUniform1i(glGetUniformLocation(shaderProgram, "roughnessMap"), 3);
    glUniform1i(glGetUniformLocation(shaderProgram, "transparencyMap"), 4);

    // Load texture
    loadTexture("test.png");
    loadTexture("sky.png");
    loadTexture("grass.png");
    loadTexture("NormalMap.png");
    loadTexture("whitr.png");
    loadTexture("black.png");
    
    std::vector<Face*> faces = 
    {
        // Sky
        new Face
        (
            std::vector<glm::vec3> { { -50, -50, -50}, { 50, -50, -50 }, { 50,  50, -50 }, { -50,  50, -50 } },
            Material("sky.png", "", "", "", "", false),
            std::vector<glm::vec2> { { 0.5f, 1 }, { 0.5f, 0.66f }, { 0.25f, 0.66f }, { 0.25f, 1 } }
        ),
        new Face
        (
            std::vector<glm::vec3> { { 50, -50, -50}, { 50, -50, 50 }, { 50,  50, 50 }, { 50,  50, -50 } },
            Material("sky.png", "", "", "", "", false),
            std::vector<glm::vec2> { { 0.5f, 0.66 }, { 0.5f, 0.33f }, { 0.25f, 0.33f }, { 0.25f, 0.66f } }
        ),
        new Face
        (
            std::vector<glm::vec3> { { 50, -50, 50}, { -50, -50, 50 }, { -50,  50, 50 }, { 50,  50, 50 } },
            Material("sky.png", "", "", "", "", false),
            std::vector<glm::vec2> { { 0.5f, 0.33 }, { 0.5f, 0 }, { 0.25f, 0 }, { 0.25f, 0.33f } }
        ),
        new Face
        (
            std::vector<glm::vec3> { { 50, 50, -50}, { 50, 50, 50 }, { -50, 50, 50 }, { -50,  50, -50 } },
            Material("sky.png", "", "", "", "", false),
            std::vector<glm::vec2> { { 0.25f, 0.66 }, { 0.25f, 0.33f }, { 0, 0.33f }, { 0, 0.66f } }
        ),
        new Face
        (
            std::vector<glm::vec3> { { -50, -50, -50}, { -50, -50, 50 }, { 50, -50, 50 }, { 50,  -50, -50 } },
            Material("sky.png", "", "", "", "", false),
            std::vector<glm::vec2> { { 0.75f, 0.66 }, { 0.75f, 0.33f }, { 0.5f, 0.33f }, { 0.5f, 0.66f } }
        ),
        new Face
        (
            std::vector<glm::vec3> { { -50, 50, -50}, { -50, 50, 50 }, { -50, -50, 50 }, { -50,  -50, -50 } },
            Material("sky.png", "", "", "", "", false),
            std::vector<glm::vec2> { { 1, 0.66 }, { 1, 0.33f }, { 0.75f, 0.33f }, { 0.75f, 0.66f } }
        ),

        // Grass
        new Face
        (
            std::vector<glm::vec3> { { -50, -50, -1}, { 50, -50, -1 }, { 50,  50, -1}, { -50,  50, -1 } },
            Material("grass.png", "", "black.png", "white.png"),
            std::vector<glm::vec2> { { 10, 10 }, { 10, 0 }, { 0, 0 }, { 0, 10 } }
        ),

        // Cube
        new Face(
            std::vector<glm::vec3> { { -1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, { -1,  1,  1} },
            Material("", "NormalMap.png"),
            std::vector<glm::vec2> { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        ),
        new Face(
            std::vector<glm::vec3> { { 1, -1, -1}, { -1, -1, -1}, { -1,  1, -1}, { 1,  1, -1} },
            Material(""),
            std::vector<glm::vec2> { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        ),
        new Face(
            std::vector<glm::vec3> { { -1, -1, -1}, { -1, -1,  1}, { -1,  1,  1}, { -1,  1, -1} },
            Material(""),
            std::vector<glm::vec2> { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        ),
        new Face(
            std::vector<glm::vec3> { { 1, -1,  1}, { 1, -1, -1}, { 1,  1, -1}, { 1,  1,  1} },
            Material(""),
            std::vector<glm::vec2> { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        ),
        new Face(
            std::vector<glm::vec3> { { -1, 1,  1}, { 1, 1,  1}, { 1, 1, -1}, { -1, 1, -1} },
            Material(""),
            std::vector<glm::vec2> { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        ),
        new Face(
            std::vector<glm::vec3> { { -1, -1, -1}, { 1, -1, -1}, { 1, -1,  1}, { -1, -1,  1} },
            Material(""),
            std::vector<glm::vec2> { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        )
    };
    
    Camera cam(glm::vec3(-2.25f,-0.5f,-0.5f), glm::vec3(glm::radians(30.0f), glm::radians(0.0f), 0.0f), glm::radians(90.0f), 16.0f / 9.0f);

    SunLight sun(glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f, 0.9f, 0.7f), 1.0f);

    std::vector<Light> lights =
    {
    };

    //
    // ======== MAIN LOOP ========
    //
    while (!glfwWindowShouldClose(window))
    {
        if (is_moving_forward)
            cam.pos += cam.getForward() * speed;
        if (is_moving_back)
            cam.pos -= cam.getForward() * speed;
        if (is_moving_left)
            cam.pos += cam.getLeft() * speed;
        if (is_moving_right)
            cam.pos -= cam.getLeft() * speed;

        if (is_looking_up)
            cam.ang.x -= sens;
        if (is_looking_down)
            cam.ang.x += sens;
        if (is_looking_left)
            cam.ang.y += sens;
        if (is_looking_right)
            cam.ang.y -= sens;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(cam.getView()));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(cam.getProj()));
        glUniform3fv(glGetUniformLocation(shaderProgram, "viewpos"), 1, glm::value_ptr(cam.pos));

        glUniform3fv(glGetUniformLocation(shaderProgram, "sun.direction"), 1, glm::value_ptr(sun.direction));
        glUniform3fv(glGetUniformLocation(shaderProgram, "sun.color"), 1, glm::value_ptr(sun.color));
        glUniform1f(glGetUniformLocation(shaderProgram, "sun.intensity"), sun.intensity);

        glUniform1i(glGetUniformLocation(shaderProgram, "numPointLights"), lights.size());
        for (int i = 0; i < lights.size(); ++i) {
            std::string baseName = "pointLights[" + std::to_string(i) + "]";
            glUniform3fv(glGetUniformLocation(shaderProgram, (baseName + ".position").c_str()), 1, glm::value_ptr(lights[i].position));
            glUniform3fv(glGetUniformLocation(shaderProgram, (baseName + ".direction").c_str()), 1, glm::value_ptr(lights[i].direction));
            glUniform1f (glGetUniformLocation(shaderProgram, (baseName + ".angle").c_str()),     lights[i].angle);
            glUniform3fv(glGetUniformLocation(shaderProgram, (baseName + ".color").c_str()),     1, glm::value_ptr(lights[i].color));
            glUniform1f (glGetUniformLocation(shaderProgram, (baseName + ".intensity").c_str()), lights[i].intensity);
        }

        for (auto face : faces)
            face->draw(shaderProgram);

        // Render the developer console (if needed)
        if (console_visible == true)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Logs");
            std::vector<char> logBuffer(logs.begin(), logs.end());
            logBuffer.push_back('\0');
            ImVec2 contentRegion = ImGui::GetContentRegionAvail();
            ImGui::InputTextMultiline(
                "##logs",
                logBuffer.data(), logBuffer.size(),
                ImVec2(contentRegion.x, contentRegion.y),
                ImGuiInputTextFlags_ReadOnly);
            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents();        // Process user input and window events
    }
    //
    // ======== END OF MAIN LOOP ========
    //

    // Clean up
    log(INFO, "Shutting down...");
    
    ImGui_ImplOpenGL3_Shutdown(); // Terminate ImGui impl for OpenGL3
    ImGui_ImplGlfw_Shutdown();    // Terminate ImGui impl for GLFW
    ImGui::DestroyContext();      // Destroy ImGui context
    closeLogFile();               // Close log file
    glfwDestroyWindow(window);    // Destroy the window
    glfwTerminate();              // Terminate GLFW
    return 0;                     // GG
}
