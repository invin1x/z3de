# z3de - Zubov's 3D engine

A simple 3D engine that I'm developing just for fun.

## Build instructions

1. **Clone the repository:**

   Use Git to clone the repository to your local machine:
   ```
   git clone https://github.com/invin1x/z3de.git
   cd z3de
   ```

2. **Install third-party dependencies:**

   Run `download_deps.py` with Python to install third-party dependencies:
   ```
   python3 download_deps.py
   ```

3. **Build the project:**

   Use CMake to generate build files:
   ```
   mkdir -p out
   cd out
   cmake ..
   ```
   Then build the project:
   ```
   make
   ```
   If there is an error, check the logs, and install the specific package.

## License

   This project is licensed under the MIT License. You can find the full license text in the [`./LICENSE.txt`](./LICENSE.txt) file in the root directory.

## Third-party dependencies

   This project uses third-party dependencies listed below. [`./download_deps.py`](./download_deps.py) downloads them all and extracts to `./thirdparty` directory. After running this script you will be able to find the licenses for these dependencies in their respective subdirectories.

### GLFW

   GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development. It provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, handling events, etc.
 - GLFW repository: [click](https://github.com/glfw/glfw.git)

### GLEW

   The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library. GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform. OpenGL core and extension functionality is exposed in a single header file. GLEW has been tested on a variety of operating systems, including Windows, Linux, Mac OS X, FreeBSD, Irix, and Solaris.
 - GLEW repository: [click](https://github.com/nigels-com/glew.git)

### GLM

   OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications. GLM provides classes and functions designed and implemented with the same naming conventions and functionality than GLSL so that anyone who knows GLSL, can use GLM as well in C++.
 - GLM repository: [click](https://github.com/g-truc/glm.git)

### STB

   Single-file public domain (or MIT licensed) libraries for C/C++.
 - STB repository: [click](https://github.com/nothings/stb.git)
