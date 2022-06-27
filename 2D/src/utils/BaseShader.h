#pragma once

#include <GLFW/glfw3.h>

class BaseShader {
public:
    unsigned int ID;
    BaseShader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);
    
    void useProgram();
    void deleteProgram();
};