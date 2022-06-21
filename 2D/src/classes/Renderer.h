#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BaseShader.h"

#include <iostream>

class Renderer{
private:
    GLFWwindow* applicationWindow;
    const char* applicationName;
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;
    BaseShader baseShader;

    void processInput(GLFWwindow* window);
    // void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    Renderer(const char* appName, unsigned int screenWidth, unsigned int screenHeight, const char* vsFilepath, const char* fsFilepath);

    void beginRenderLoop();
};