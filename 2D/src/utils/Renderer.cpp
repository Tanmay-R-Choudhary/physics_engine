#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "BaseShader.h"

#include <iostream>

Renderer::Renderer(const char* appName, unsigned int screenWidth, unsigned int screenHeight) {
    windowName = appName;
    SCR_WIDTH = screenWidth;
    SCR_HEIGHT = screenHeight;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    applicationWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, appName, NULL, NULL);

    glfwMakeContextCurrent(applicationWindow);

    glfwSetWindowAttrib(applicationWindow, GLFW_RESIZABLE, false);
    gladLoadGL();

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(applicationWindow, true);
    ImGui_ImplOpenGL3_Init("version 330");



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