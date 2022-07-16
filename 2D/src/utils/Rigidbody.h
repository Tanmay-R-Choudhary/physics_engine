#pragma once

#include "BaseShader.h"

class Rigidbody 
{
private:
    float vertices[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    unsigned int VAO;
    unsigned int VBO;
public:
    BaseShader shader;
    Rigidbody(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);

    void drawBody();
    void releaseResources();
};