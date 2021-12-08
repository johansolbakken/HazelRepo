//
//  Window.h
//  ui
//
//  Created by Johan Solbakken on 08/12/2021.
//

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window {
public:
    Window();
    Window(int32_t width, int32_t height);
    ~Window();
    
    void Initialize();
    bool WindowShouldClose();
    void SwapBuffers();
private:
    GLFWwindow* m_mainWindow;
    int32_t m_width;
    int32_t m_height;
};
