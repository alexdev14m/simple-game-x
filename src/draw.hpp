#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"

class Draw {
public:
    static void drawPyramid(float* array, size_t totalSize,const size_t elm_per_row) {
        size_t numRows = totalSize / elm_per_row;

        for (size_t i = 0; i < numRows - 1; ++i) {
            glDrawArrays(GL_TRIANGLES, i * 3, 3); 
        }
    }
};