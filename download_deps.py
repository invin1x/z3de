import requests
import zipfile
import os
import shutil

# Deps URLs
deps = [
    "https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip",
    "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip",
    "https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip",
    "https://github.com/nothings/stb/archive/refs/heads/master.zip",
    "https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.zip"
]

# Download and unpack
for dep in deps:
    print("\nDownloading\"" + dep + "\"...")
    with open("DownloadCache", "wb") as zip_file:
        zip_file.write(requests.get(dep).content)
    print("Extracting...")
    with zipfile.ZipFile("DownloadCache", "r") as zip_ref:
        zip_ref.extractall("./thirdparty")
os.remove("DownloadCache")
print("\nDone!")
