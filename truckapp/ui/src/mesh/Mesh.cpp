//
//  Mesh.cpp
//  ui
//
//  Created by Johan Solbakken on 08/12/2021.
//

#include "Mesh.hpp"

Mesh::Mesh() {}

void Mesh::SetVertices(GLfloat vertices[], int32_t amount) {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * amount, vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

Mesh::~Mesh() {
    m_VAO = 0;
    m_VBO = 0;
}

void Mesh::Bind() {
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void Mesh::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
