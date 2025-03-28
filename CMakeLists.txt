cmake_minimum_required(VERSION 3.16)

project("z3de")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.4")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/glew-2.2.0/build/cmake")

add_executable(z3de)

# Source files
target_sources(z3de PRIVATE
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

# Include catalogs
target_include_directories(z3de PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.4/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/glew-2.2.0/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/glm"
    "${CMAKE_SOURCE_DIR}/thirdparty/stb-master"
)

# Libraries
target_link_libraries(z3de PRIVATE
    OpenGL::GL
    OpenGL::GLU
    glfw
    glew
)
