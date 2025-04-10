#!/usr/bin/env python3

from pathlib import Path

with Path("include/shader_sources.hpp").open("w", encoding="utf-8") as out:
    out.write("#ifndef SHADER_SOURCES_HPP\n")
    out.write("#define SHADER_SOURCES_HPP\n\n")
    out.write("// This header is being generated automaticly on build!!!\n")
    out.write("// If you want to edit shaders, edit \"src/shader_sources/<your_shader>.glsl\"\n\n")

    # Vertex shader
    with Path("src/shader_sources/vertex.glsl").open("r", encoding="utf-8") as f:
        contents = f.read()
        out.write("const char* SHADER_VERTEX_SOURCE = R\"(")
        out.write(contents)
        out.write(")\";\n\n")

    # Fragment shader
    with Path("src/shader_sources/fragment.glsl").open("r", encoding="utf-8") as f:
        contents = f.read()
        out.write("const char* SHADER_FRAGMENT_SOURCE = R\"(")
        out.write(contents)
        out.write(")\";\n\n")

    out.write("\n#endif // SHADER_SOURCES_HPP\n")
