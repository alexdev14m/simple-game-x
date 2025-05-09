#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shaders {
    public:
        Shaders(const std::string vertexShPath, const std::string fragmentShPath)
            : vertexShaderCode(readShader(vertexShPath)), fragmentShaderCode(readShader(fragmentShPath)) {}

        std::string readShader(const std::string path){
            std::ifstream shader(path);

            if (!shader.is_open()){
                std::cerr << "Error: Couldn't open the shader file: " << path << std::endl;
                
                return "";
            }

            std::stringstream buffer;
            buffer << shader.rdbuf();
            
            return buffer.str();
        }
        
        static bool makeShader(unsigned int shaderVar, const std::string shaderCode) {
            if (!shaderVar){
                std::cerr << "Error: The shader variable is NULL/empty, please give it a value!" << std::endl;
                return false;
            }
            
            const char* shaderSource = shaderCode.c_str(); 

            glShaderSource(shaderVar, 1, &shaderSource, NULL);
            glCompileShader(shaderVar);

            int success;
            char infolog[512];
            glGetShaderiv(shaderVar, GL_COMPILE_STATUS, &success);

            if(!success) {
                std::cerr << "Error: Could't compile the shader." << std::endl;
            }

            std::cout << "Successfully made the shader!" << std::endl;
            
            return true;
        }

        std::string getVShaderCode() const { return vertexShaderCode; }
        std::string getFShaderCode() const { return fragmentShaderCode; }

        void printShaderCodes() {
            std::cout << "Vertex Shader Code:\n" << getVShaderCode() << std::endl;
            std::cout << "Fragment Shader Code:\n" << getFShaderCode() << std::endl;
        }


    private:
        std::string vertexShaderCode;
        std::string fragmentShaderCode;
};

class Utils {
    public:
        static bool genVBO(unsigned int &VBOVar){
            glGenBuffers(1, &VBOVar);
            glBindBuffer(GL_ARRAY_BUFFER, VBOVar);

            return true;
        }
};