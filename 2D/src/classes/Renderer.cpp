#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "BaseShader.h"

#include <iostream>

Renderer::Renderer(const char* appName, unsigned int screenWidth, unsigned int screenHeight, const char* vsFilepath, const char* fsFilepath) : baseShader(vsFilepath, fsFilepath) {
    applicationName = appName;
    SCR_WIDTH = screenWidth;
    SCR_HEIGHT = screenHeight;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    applicationWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, appName, NULL, NULL);

    glfwMakeContextCurrent(applicationWindow);
    // glfwSetFramebufferSizeCallback(applicationWindow, frameBufferSizeCallback);

    int w, h;
    glfwGetWindowSize(applicationWindow, &w, &h);
    glViewport(0, 0, w, h);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

// void Renderer::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

void Renderer::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Renderer::beginRenderLoop() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 


    while (!glfwWindowShouldClose(applicationWindow)) {
        processInput(applicationWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        baseShader.useProgram();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(applicationWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    baseShader.deleteProgram();

    glfwTerminate();
}