#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* win;
int winsize[2] = {800, 600};
            //  w    h
const char* title = "OpenGL Window";

bool initGLFW(){
    if (!glfwInit())
    {
        std::cerr << "Error: Failed to load GLFW3!" << std::endl;
        return false;
    }

    std::cout << "Successfully loaded GLFW3!" << std::endl;

    return true;
}
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
bool loadGLAD(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Error: Failed to load GLAD" << std::endl;
        glfwTerminate();
        return false;
    }

    std::cout << "Successfully loaded GLAD\nFinishing loading libraries..." << std::endl;

    return true;
}

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

void winLoop(GLFWwindow* window){
    std::cout << "Looping the window!" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
}

int main(int argc, char const *argv[])
{
    if(!initializelibs()){
        std::cout << "Error: Failed to initialize libraries" << std::endl;
        return -1;
    }

    winLoop(win);

    glfwTerminate();

    return 0;
}
