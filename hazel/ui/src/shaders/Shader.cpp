//
//  Shader.cpp
//  ui
//
//  Created by Johan Solbakken on 08/12/2021.
//

#include "Shader.h"

class CouldNotCreateShader{};

Shader::Shader(std::string vertexShader, std::string fragmentShader)
: m_vertexShader(vertexShader), m_fragmentShader(fragmentShader)
{
    m_shaderID = glCreateProgram();
    if (!m_shaderID) {
        throw CouldNotCreateShader{};
    }
    
    AddShader(m_shaderID, m_vertexShader, GL_VERTEX_SHADER);
    AddShader(m_shaderID, m_fragmentShader, GL_FRAGMENT_SHADER);
    
    glLinkProgram(m_shaderID);
    glValidateProgram(m_shaderID);
}

Shader::~Shader() {
    m_shaderID = 0;
}

void Shader::useShader() {
    glUseProgram(m_shaderID);
}

void Shader::AddShader(GLuint program, std::string filepath, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    std::string code = GetCode(filepath);
    const GLchar* theCode[1];
    theCode[0] = code.c_str();
    glShaderSource(shader, 1, theCode, NULL);
    glCompileShader(shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}


std::string Shader::GetCode(std::string filepath) {
    std::ifstream file(filepath, std::ios::in);
    std::stringstream stringstream;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            stringstream << line << "\n";
        }
        file.close();
    } else {
        std::cout << "The file " << filepath << " did not exist!"<< std::endl;
    }
    return stringstream.str();
}

GLint Shader::GetUniformLocation(std::string varName) {
    return glGetUniformLocation(m_shaderID, varName.c_str());
}
