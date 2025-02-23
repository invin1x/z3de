# z3de - Zubov's 3D engine

A simple 3D engine that i'm developing just for fun.

## Build instructions
1. **Clone the Repository**  
   Use Git to clone the repository to your local machine:
   ```
   git clone https://your-repo-url.git
   ```

2. **Install Dependencies**  
   Run the following command to install all third-party dependencies:
   ```
   python download_externals.py
   ```

3. **Generate Build Files**  
   Use CMake to generate the necessary build files:
   ```
   mkdir -p out/build
   cd out/build
   cmake ..
   ```

4. **Build the Project**  
   Compile the project with your chosen build system (e.g., Make, Ninja):
   ```
   make
   ```

## License

This project is licensed under the [MIT License](LICENSE.txt). You can find the full license text in the `LICENSE.txt` file in the root directory.

### Third-Party Dependencies

**z3de** also uses third-party dependencies, each with its own license. The `download_externals.py` script will download these dependencies and store them in the `external` directory. You can find the licenses for these dependencies in their respective subdirectories.
