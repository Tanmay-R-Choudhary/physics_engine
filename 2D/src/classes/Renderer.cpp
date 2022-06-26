#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "BaseShader.h"

#include <iostream>

Renderer::Renderer(const char* appName, unsigned int screenWidth, unsigned int screenHeight) {
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
    gladLoadGL();
    // glfwSetFramebufferSizeCallback(applicationWindow, frameBufferSizeCallback);

    int w, h;
    glfwGetWindowSize(applicationWindow, &w, &h);
    glViewport(0, 0, w, h); //ERROR HERE

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Renderer::addBodyTorigidbodyList(Rigidbody body) {
    rigidbodyList.push_back(body);
}

void Renderer::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Renderer::beginRenderLoop() {

    while (!glfwWindowShouldClose(applicationWindow)) {
        processInput(applicationWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Rigidbody rb : rigidbodyList) {
            rb.drawBody();
        }

        glfwSwapBuffers(applicationWindow);
        glfwPollEvents();
    }

    for (Rigidbody rb : rigidbodyList) {
        rb.releaseResources();
    }

    glfwTerminate();
}