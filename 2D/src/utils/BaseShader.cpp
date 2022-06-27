#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BaseShader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

BaseShader::BaseShader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath) {
    std::string vsSourceCode, fsSourceCode;
    std::ifstream vsFile, fsFile;
    
    vsFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fsFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vsFile.open(vertexShaderFilepath);
        fsFile.open(fragmentShaderFilepath);
        
        std::stringstream vsStream, fsStream;
        
        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();
        
        vsFile.close();
        fsFile.close();
        
        vsSourceCode = vsStream.str();
        fsSourceCode = fsStream.str();
    } catch(std::ifstream::failure e) {
        printf("ERROR::SHADER::FILE_NOT_READ\n");
    }

    const char* vsCode;
    const char* fsCode;
    
    vsCode = vsSourceCode.c_str();
    fsCode = fsSourceCode.c_str();
    
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vsCode, nullptr);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR COMPILING VERTEX SHADER: " << std::endl << infoLog << std::endl;
    }
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fsCode, nullptr);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR COMPILING FRAGMENT SHADER: " << std::endl << infoLog << std::endl;
    }
    
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR LINKING PROGRAM" <<std::endl << infoLog << std::endl;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void BaseShader::useProgram() {
    glUseProgram(ID);
}

void BaseShader::deleteProgram() {
    glDeleteProgram(ID);
}
