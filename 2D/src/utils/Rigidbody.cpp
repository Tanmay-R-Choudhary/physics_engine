#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rigidbody.h"
#include "BaseShader.h"

Rigidbody::Rigidbody(const char* vertexShaderFilepath, const char* fragmentShaderFilepath) : shader(vertexShaderFilepath, fragmentShaderFilepath) 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

void Rigidbody::drawBody() 
{
    shader.useProgram();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
    glBindVertexArray(0);
}

void Rigidbody::releaseResources() 
{
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.deleteProgram();
}