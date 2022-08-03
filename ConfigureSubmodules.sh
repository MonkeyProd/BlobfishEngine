git submodule update --force --init --recursive --remote
cd Blobfish/extern/glfw
git checkout 3.3-stable
cd ../imgui
git checkout docking
cd ../tracy
git checkout tags/v0.8.2
cd ../../../