//
//  Mesh.hpp
//  ui
//
//  Created by Johan Solbakken on 08/12/2021.
//

#pragma once

#include "GL/glew.h"

class Mesh {
public:
    Mesh();
    ~Mesh();
    
    void SetVertices(GLfloat* vertices, int32_t amount);
    
    void Bind();
    void Unbind();
    
    void Draw();

private:
    GLuint m_VAO, m_VBO;
};
