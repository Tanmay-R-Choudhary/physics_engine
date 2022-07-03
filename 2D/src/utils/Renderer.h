#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "BaseShader.h"
#include "Rigidbody.h"

#include <iostream>

class Renderer{
private:
    GLFWwindow* applicationWindow;
    const char* windowName;
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;

    std::vector<Rigidbody> rigidbodyList;

    void processInput(GLFWwindow* window);

public:
    Renderer(const char* appName, unsigned int screenWidth, unsigned int screenHeight);

    void addBodyTorigidbodyList(Rigidbody body);

    void beginRenderLoop();
};