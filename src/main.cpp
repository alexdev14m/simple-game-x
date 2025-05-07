#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// * Already declared the variables
GLFWwindow* win;
int winsize[2] = {800, 600};
            //  w    h
const char* title = "OpenGL Window";

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

void regInputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void changeWinColor(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

// * The loop for the window
void winLoop(GLFWwindow* window){
    std::cout << "Looping the window!" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        regInputs(win);
        changeWinColor(0.2f,0.3f,0.3f,1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
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
