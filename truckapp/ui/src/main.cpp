#include <string>

#include "window/Window.h"
#include "shaders/Shader.h"


int main(void)
{
    Window window;
    window.Initialize();
    
    // Data
    GLfloat vertices[] = {
        1.0f, -1.0f, -1.0f,
        -1.0, -1.0f, -1.0f,
        0.0f, 1.0f, 0.0f,
    };
    
    // Create objects
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    Shader program("../../ui/res/shaders/vertex.glsl", "../../ui/res/shaders/fragment.glsl");
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    /* Loop until the user closes the window */
    while (!window.WindowShouldClose())
    {
        glfwPollEvents();
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        glBindVertexArray(VAO);
        program.useShader();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
        glBindVertexArray(0);
        
        /* Swap front and back buffers */
        window.SwapBuffers();
    }

    glfwTerminate();
 
    return 0;
}
