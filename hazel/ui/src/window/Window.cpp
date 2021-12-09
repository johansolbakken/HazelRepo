//
//  Window.cpp
//  ui
//
//  Created by Johan Solbakken on 08/12/2021.
//

#include "Window.h"

class glfwInitFailed {};
class glewInitFailed {};
class windowInitFailed {};

Window::Window() : m_width(800), m_height(600) {}
Window::Window(int32_t width, int32_t height) : m_width(width), m_height(height) {}

void Window::Initialize() {
    /* Initialize the library */
    if (!glfwInit()) {
        throw glfwInitFailed();
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
    m_mainWindow = glfwCreateWindow(m_width, m_height, "Hello World", NULL, NULL);
    if (!m_mainWindow)
    {
        glfwTerminate();
        throw windowInitFailed();
    }

    // Get Buffer size information
    int32_t bufferWidth, bufferHeight;
    glfwGetFramebufferSize(m_mainWindow, &bufferWidth, &bufferHeight);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(m_mainWindow);

    // Allow to use extensions
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
        throw glewInitFailed();
    }
    
    // Setup Viewport size
    glViewport(0,0, bufferWidth, bufferHeight);
}

bool Window::WindowShouldClose() {
    return glfwWindowShouldClose(m_mainWindow);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_mainWindow);
}

Window::~Window() {
    glfwDestroyWindow(m_mainWindow);
}
