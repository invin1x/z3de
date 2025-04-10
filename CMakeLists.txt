cmake_minimum_required(VERSION 3.16)

project("z3de")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_custom_target(copy_shader_sources ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Running \"gen_shaders.py\"..."
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/gen_shaders.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

find_package(OpenGL REQUIRED)
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.4")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/glew-2.2.0/build/cmake")

add_executable(z3de)

# Source files
target_sources(z3de PRIVATE
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/logging.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/textures.cpp"
    "${CMAKE_SOURCE_DIR}/src/shaders.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/face.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/camera.cpp"
    
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
    "${CMAKE_SOURCE_DIR}/include"
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
