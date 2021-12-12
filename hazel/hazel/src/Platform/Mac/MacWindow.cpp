#include "MacWindow.h"

#include "hzpch.h"

namespace Hazel {

static bool s_GLFWInitialzed = false;

Window* Window::Create(const WindowProps& props) {
    return new MacWindow(props);
}

MacWindow::MacWindow(const WindowProps& props) {
    Init(props);
}

MacWindow::~MacWindow() {
    Shutdown();
}
                

void MacWindow::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void MacWindow::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
    m_Data.VSync = enabled;
}

bool MacWindow::IsVSync() const {
    return m_Data.VSync;
}

void MacWindow::Init(const WindowProps& props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    
    HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
 
    if (!s_GLFWInitialzed) {
        int success = glfwInit();
        HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
        s_GLFWInitialzed = true;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti aliasing
    // Core profile - no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
    
}

void MacWindow::Shutdown() {
    glfwDestroyWindow(m_Window);
}

}
