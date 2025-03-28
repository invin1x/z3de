#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <ctime>

enum LogType{ INFO, WARN, ERROR, FATAL };

void Log(LogType type, std::string text)
{
    std::string typeStr =
        (type == INFO) ? "\033[92mINFO " :
        (type == WARN) ? "\033[93mWARN " :
        (type == ERROR) ? "\033[91mERROR" :
        "\033[91mFATAL";
    text =
        (type == INFO) ? "\033[2m\033[37m" + text :
        (type == WARN) ? "\033[97m" + text :
        (type == ERROR) ? "\033[93m" + text :
        "\033[91m" + text;
    
    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);
    char timeStr[13];
    std::sprintf(timeStr, "\033[96m%02d:%02d:%02d", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

    std::cout << timeStr << " " << typeStr << " " << text << "\033[0m" << std::endl;
}

// The entry point
int main()
{
    // Init GLFW
    if(!glfwInit())
    {
        Log(FATAL, "GLFW initialization error.");
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "z3de", nullptr, nullptr);
    if (!window)
    {
        Log(FATAL, "Creating window error.");
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context of the window current
    glfwMakeContextCurrent(window);

    //
    // ======== MAIN LOOP ========
    //
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the window

        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents(); // Process user input and window events
    }
    //
    // ======== END OF MAIN LOOP ========
    //

    // Clean up
    Log(INFO, "Shutting down..");
    glfwDestroyWindow(window); // Destroy the window
    glfwTerminate();           // Terminate GLFW
    return 0;                  // GG
}
