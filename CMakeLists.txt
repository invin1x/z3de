project("z3de")

# Generate "vertex.h" from "vertex.glsl"
file(READ "${CMAKE_SOURCE_DIR}/src/shaders/vertex.glsl" VERTEX_SHADER_SRC)
file(WRITE "${CMAKE_SOURCE_DIR}/include/shaders/vertex.h" "//\n// This header file contains the source code of the shader \"src/shaders/vertex.glsl\" and is regenerated with each CMake generation.\n// If you need to modify the source code of a shader, edit the corresponding file in the \"src/shaders\" directory.\n//\n\n#ifndef VERTEX_H\n#define VERTEX_H\n\nconstexpr char VERTEX_SHADER_SRC[] = R\"(${VERTEX_SHADER_SRC})\";\n\n#endif // VERTEX_H\n")

# Generate "fragment.h" from "fragment.glsl"
file(READ "${CMAKE_SOURCE_DIR}/src/shaders/fragment.glsl" FRAGMENT_SHADER_SRC)
file(WRITE "${CMAKE_SOURCE_DIR}/include/shaders/fragment.h" "//\n// This header file contains the source code of the shader \"src/shaders/fragment.glsl\" and is regenerated with each CMake generation.\n// If you need to modify the source code of a shader, edit the corresponding file in the \"src/shaders\" directory.\n//\n\n#ifndef FRAGMENT_H\n#define FRAGMENT_H\n\nconstexpr char FRAGMENT_SHADER_SRC[] = R\"(${FRAGMENT_SHADER_SRC})\";\n\n#endif // FRAGMENT_H\n")

# Source files
add_executable(z3de
    "src/main.cpp"
    "src/engine/Camera.cpp"
    "src/engine/Mesh.cpp"
)

# Include directories
target_include_directories(z3de PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/glew-2.2.0/include"
    "${CMAKE_SOURCE_DIR}/external/glfw-3.4.bin.WIN32/include"
    "${CMAKE_SOURCE_DIR}/external/glm"
    "${CMAKE_SOURCE_DIR}/external/stb-master"
)

# Library files
target_link_libraries(z3de PRIVATE
    opengl32
    "${CMAKE_SOURCE_DIR}/external/glew-2.2.0/lib/Release/Win32/glew32s.lib"
    "${CMAKE_SOURCE_DIR}/external/glfw-3.4.bin.WIN32/lib-vc2022/glfw3.lib"
)
