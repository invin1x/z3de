#include <iostream>
#include "logging.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "bindings.hpp"
#include <vector>

bool console_visible = false;

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

    // Initialize ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    //
    // ======== MAIN LOOP ========
    //
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the window
        
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
