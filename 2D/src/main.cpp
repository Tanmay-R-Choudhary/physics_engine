#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/Renderer.h"
#include "utils/Rigidbody.h"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main()
{
    Renderer renderObj("Test window", SCR_WIDTH, SCR_HEIGHT);

    Rigidbody first("res/shaders/base.vs", "res/shaders/base.fs");

    renderObj.addBodyTorigidbodyList(first);
    renderObj.beginRenderLoop();
}