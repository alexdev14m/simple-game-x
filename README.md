# simple-game-x

command for compiling:
g++ main.cpp glad.c -o gamex -lglfw -ldl -lGL -g

# Currently compiling only for linux!!!

To _compile_ unzip the glad.zip open the includes folder, then copy KHR and GLAD folders into /usr/local/include
After that you can finally **compile**, most importantly, you can delete the extracted folders and the .zip file :)

REQUIREMENTS:
OpenGL 4.3+ (4.3 is the best currently)


To install OpenGL just use
sudo apt-get update
sudo apt-get install cmake pkg-config
sudo apt-get install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libglew-dev libglfw3-dev libglm-dev
sudo apt-get install libao-dev libmpg123-dev

# [Source](https://medium.com/geekculture/a-beginners-guide-to-setup-opengl-in-linux-debian-2bfe02ccd1e)
