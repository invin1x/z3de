import requests
import zipfile
import os
import shutil

# External dependencies URLs that need to be downloaded and unpacked
exts = [
    "http://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip", # GLEW
    "http://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN32.zip",            # GLFW
    "http://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip",            # GLM
    "http://github.com/nothings/stb/archive/refs/heads/master.zip"                         # STB
]

# If the directory "external" exists, show warning message
if os.path.exists("./external") and os.path.isdir("./external"):
    if len(os.listdir("./external")) > 0:
        print("Directory \"external\" already exists and is not empty. Its content will be removed.")
        print("Would you like to continue?")
        if input() != "yes":
            exit()
        shutil.rmtree('./external')

# Download and unpack external dependencies
for ext in exts:
    print("")
    print("Downloading \"" + ext + "\"...")
    with open("DownloadCache", "wb") as zip_file:
        zip_file.write(requests.get(ext).content)
    print("Extracting...")
    with zipfile.ZipFile("DownloadCache", "r") as zip_ref:
        zip_ref.extractall("./external")
os.remove("DownloadCache")

# Display completion message
print("")
print("Done.")
input("Press enter to exit.")
