//
//  Shader.h
//  ui
//
//  Created by Johan Solbakken on 08/12/2021.
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "GL/glew.h"

class Shader {
public:
    Shader(std::string vertexShader, std::string fragmentShader);
    ~Shader();
    void useShader();
    
private:
    std::string GetCode(std::string filepath);
    void AddShader(GLuint program, std::string filepath, GLenum shaderType);
    
private:
    GLuint m_shaderID;
    std::string m_vertexShader;
    std::string m_fragmentShader;
};
