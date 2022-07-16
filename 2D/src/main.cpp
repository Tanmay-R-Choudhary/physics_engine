#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/Renderer.h"
#include "utils/Rigidbody.h"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 1000;

int main()
{
    Renderer renderObj("Test window", SCR_WIDTH, SCR_HEIGHT);

    Rigidbody first("res/shaders/standard/base.vs", "res/shaders/standard/base.fs");

    renderObj.addBodyTorigidbodyList(first);
    renderObj.beginRenderLoop();
}