#pragma once

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

            if (!success) {
                glGetShaderInfoLog(shaderVar, 512, NULL, infolog);
                std::cerr << "Error: Could't compile the shader. Log: " << infolog << std::endl;
                return false;
            }

            std::cout << "Successfully made the shader!" << std::endl;

            return true;
        }

        static bool attachShader(unsigned int program, unsigned int shader){
            glAttachShader(program, shader);
            glLinkProgram(program);

            int success;
            char infolog[512];
            glGetProgramiv(program, GL_LINK_STATUS, & success);
            if (!success){
                glGetProgramInfoLog(program, 512, NULL, infolog);
                std::cerr << "Error: Couldn't attach the shader to the program! Log: " << infolog << std::endl;

                return false;
            }

            std::cout << "Successfully attached the shader to the program!" << std::endl;

            return true;
        }

        static void rmShad(unsigned int shader) {
            std::cout << "Removed the shader!" << std::endl;
            glDeleteShader(shader);
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
    static bool genVBO(unsigned int &VBOVar) {
        glGenBuffers(1, &VBOVar);
        glBindBuffer(GL_ARRAY_BUFFER, VBOVar);
        return true;
    }

    static void interVertData() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        std::cout << "Successfully told OpenGL how to interpret vertex data!" << std::endl;
    }

    // Uploads data to currently bound VBO
    static void uploadToVBO(const float* data, size_t sizeInBytes) {
        glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
        std::cout << "Uploaded " << sizeInBytes << " bytes to the VBO." << std::endl;
    }

    // Generic function to calculate number of elements in an array
    template<typename T, size_t N>
    static constexpr size_t calculateNumOfElm(const T (&)[N]) {
        return N;
    }
};
