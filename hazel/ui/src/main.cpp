#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/vec4.hpp"

#include "window/Window.h"
#include "shaders/Shader.h"
#include "mesh/Mesh.hpp"

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
    
    Mesh mesh;
    mesh.SetVertices(vertices, 9);
    
    Shader program("../../ui/res/shaders/vertex.glsl", "../../ui/res/shaders/fragment.glsl");
    
    /* Loop until the user closes the window */
    while (!window.WindowShouldClose())
    {
        glfwPollEvents();
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mesh.Bind();
        program.useShader();
        glUniform4f(program.GetUniformLocation("ourColor"), 1.0f, sin(glfwGetTime()/2.0+0.5), 1.0f, 1.0f);
        mesh.Draw();
        glUseProgram(0);
        mesh.Unbind();
        
        /* Swap front and back buffers */
        window.SwapBuffers();
    }

    glfwTerminate();
 
    return 0;
}
