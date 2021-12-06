#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

// Window dimensions
const int32_t WIDTH = 800, HEIGHT = 600;

int main(void)
{
    
    /* Initialize the library */
    if (!glfwInit()) {
        printf("GLFW initialization failed!\n");
        return 1;
    }
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti aliasing
    // Core profile - no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create window
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!mainWindow)
    {
        glfwTerminate();
        printf("Could not create window!\n");
        return 1;
    }

    // Get Buffer size information
    int32_t bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(mainWindow);

    // Allow to use extensions
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        printf("Glew initialization failed!\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    
    // Setup Viewport size
    glViewport(0,0, bufferWidth, bufferHeight);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();
        glClearColor(1.f, 0.f, 0.f, 1.f);
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(mainWindow);
    }

    glfwTerminate();
 
    return 0;
}
