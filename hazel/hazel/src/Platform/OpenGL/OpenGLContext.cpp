//
//  OpenGLContext.cpp
//  Hazel
//
//  Created by Johan Solbakken on 22/12/2021.
//

#include "hzpch.h"
#include "OpenGLContext.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{
    HZ_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    HZ_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}

}