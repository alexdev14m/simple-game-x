#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "utils.hpp"
#include "draw.hpp"

float vertices[] = {
    0.0f,0.5f,0.0f,
    0.5f,0.0f,0.5f,
    -0.5f,0.0f,0.5f,
    -0.5f,0.0f,-0.5f,
    0.5f,0.0f,-0.5f
};

// * Already declared the variables
GLFWwindow* win;
int winsize[2] = {800, 600};
            //  w    h
const char* title = "OpenGL Window";

unsigned int vertShader;
unsigned int fragShader;
unsigned int VBO;
unsigned int VAO;
unsigned int shaderProgram;

// * Initializing GLFW
// ! Do NOT touch or change, unless needed
bool initGLFW(){
    if (!glfwInit())
    {
        std::cerr << "Error: Failed to load GLFW3!" << std::endl;
        return false;
    }

    std::cout << "Successfully loaded GLFW3!" << std::endl;

    return true;
}

// * Making the window, that way we can load (initialize) GLAD
// ! Do NOT touch or change, unless needed
bool makeWindow(int w,int h,const char* name){
    win = glfwCreateWindow(w, h, name, nullptr, nullptr);

    if (!win){
        std::cerr << "Error: Failed to create the window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(win);
    
    std::cout << "Successfully made the window!" << std::endl;

    return true;
}

// * Loading (Initializing) GLAD
// ! Do NOT touch or change, unless needed
bool loadGLAD(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Error: Failed to load GLAD" << std::endl;
        glfwTerminate();
        return false;
    }

    std::cout << "Successfully loaded GLAD\nFinishing loading libraries..." << std::endl;

    return true;
}

// ** Initialize everything
// ! Do NOT touch or change, unless needed
bool initializelibs(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(!initGLFW() || !makeWindow(winsize[0], winsize[1], title) || !loadGLAD()){
        glfwTerminate();
        return false;
    }
    glViewport(0,0,winsize[0],winsize[1]);

    return true;
}

// *Registers input
// TODO: Can be changed, ONLY when adding new inputs, otherwise do NOT touch.
void regInputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// * Assigning the window a background color
// ! Do NOT touch or change, at all unless you know what you're doing
bool changeWinColor(float r, float g, float b, float a){
    if (std::isnan(r) || std::isnan(g) || std::isnan(b) || std::isnan(a) ||
        r < 0.0f || r > 1.0f || g < 0.0f || g > 1.0f || b < 0.0f || b > 1.0f || a < 0.0f || a > 1.0f) {
        std::cerr << "Error: One or more of the color values are invalid. Valid range is [0.0, 1.0].\n";
        return false;
    }
    
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
    return true;
}

// * The loop for the window
bool winLoop(GLFWwindow* window){
    std::cout << "Looping the window!" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        regInputs(win);
        if(!changeWinColor(0.2f,0.3f,0.3f,1.0f)) {
            std::cerr << "Setting colors failed!" << std::endl;
            return false;
        }        

        Draw::drawPyramid(vertices, Utils::calculateNumOfElm(vertices), 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return true;
}
// # MAIN LOOP
int main(int argc, char const *argv[])
{

    // * Handling the the worst case scenario
    if(!initializelibs()){
        std::cerr << "Error: Failed to initialize libraries" << std::endl;
        return -1;
    }

    // ! DO NOT TOUCH THIS ASSIGNMENT OF VALUE! IT CAN BREAK A TON OF STUFF!
    vertShader = glCreateShader(GL_VERTEX_SHADER); // * Assignment of the Vertex Shader
    fragShader = glCreateShader(GL_FRAGMENT_SHADER); // * Assignment of the Fragment Shader

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // * Handling the errors that could happen during generation of VBO
    if(!Utils::genVBO(VBO)) {
        std::cerr << "Error: Failed to generate VBO." << std::endl;
        return -1;
    }
    
    

    std::cout << "Generated VBO!" << std::endl;

    Utils::uploadToVBO(vertices, sizeof(vertices));

    Utils::interVertData(); // * A simple function which tells OpenGL how to interpret Vertex Data

    Shaders shade("shaders/vertShader.glsl", "shaders/fragShader.glsl"); // # Just calling the constructor here nothing much

    // * Here I'm actually compiling the shaders, making them usable
    // ! Do not mess with this, it's just some setup code, it won't alter the result of the graphics. Well if messed with it might just not even work.

    if(!Shaders::makeShader(vertShader, shade.getVShaderCode())){
        std::cerr << "Failed to make the vertex shader!" << std::endl;
        return -1;
    }

    if(!Shaders::makeShader(fragShader, shade.getFShaderCode())){
        std::cerr << "Failed to make the fragment shader!" << std::endl;
        return -1;
    }

    shaderProgram = glCreateProgram(); // * Creation of the program

    // * Simple and clean attachments of shaders
    Shaders::attachShader(shaderProgram, vertShader);
    Shaders::attachShader(shaderProgram, fragShader);

    glUseProgram(shaderProgram);
    Draw::drawPyramid(vertices, Utils::calculateNumOfElm(vertices), 3);

    // * Simple and clean removal of shaders
    Shaders::rmShad(vertShader);
    Shaders::rmShad(fragShader);

    // * Handling the worst case scenario No. 2
    if(!winLoop(win)){
        std::cerr << "Failed to loop the Mr. Loop!" << std::endl;
        
        return -1;
    }
    
    glfwTerminate(); // # Ending it!

    return 0;
}
