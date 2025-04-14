cmake_minimum_required(VERSION 3.16)

project(z3de)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.4")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/glew-2.2.0/build/cmake")

add_executable(z3de)



file(READ "${CMAKE_SOURCE_DIR}/src/render/shaders/vertex.glsl" VERTEX_SHADER_SOURCE)
string(REPLACE "\\" "\\\\" VERTEX_SHADER_SOURCE "${VERTEX_SHADER_SOURCE}")
string(REPLACE "\"" "\\\"" VERTEX_SHADER_SOURCE "${VERTEX_SHADER_SOURCE}")
string(REPLACE "\n" "\\n" VERTEX_SHADER_SOURCE "${VERTEX_SHADER_SOURCE}")
string(REPLACE "\r" "" VERTEX_SHADER_SOURCE "${VERTEX_SHADER_SOURCE}")

file(READ "${CMAKE_SOURCE_DIR}/src/render/shaders/fragment.glsl" FRAGMENT_SHADER_SOURCE)
string(REPLACE "\\" "\\\\" FRAGMENT_SHADER_SOURCE "${FRAGMENT_SHADER_SOURCE}")
string(REPLACE "\"" "\\\"" FRAGMENT_SHADER_SOURCE "${FRAGMENT_SHADER_SOURCE}")
string(REPLACE "\n" "\\n" FRAGMENT_SHADER_SOURCE "${FRAGMENT_SHADER_SOURCE}")
string(REPLACE "\r" "" FRAGMENT_SHADER_SOURCE "${FRAGMENT_SHADER_SOURCE}")

configure_file(${CMAKE_SOURCE_DIR}/src/config.hpp.in ${CMAKE_BINARY_DIR}/config.hpp)



# Source files
target_sources(z3de PRIVATE
    # z3de sources
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/interactions/logging.cpp"
    "${CMAKE_SOURCE_DIR}/src/render/material.cpp"
    "${CMAKE_SOURCE_DIR}/src/render/shaders.cpp"
    "${CMAKE_SOURCE_DIR}/src/render/face.cpp"
    "${CMAKE_SOURCE_DIR}/src/render/camera.cpp"
    
    # ImGui sources
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b/imgui_widgets.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b/backends/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b/backends/imgui_impl_opengl3.cpp"
)

# Include catalogs
target_include_directories(z3de PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.4/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/glew-2.2.0/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/glm"
    "${CMAKE_SOURCE_DIR}/thirdparty/stb-master"
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.91.9b"
)

# Libraries
target_link_libraries(z3de PRIVATE
    OpenGL::GL
    OpenGL::GLU
    glfw
    glew_s
)
