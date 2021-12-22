#include "hzpch.h"
#include "MacWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Hazel
{

static bool s_GLFWInitialzed = false;

static void GLFWErrorCallback(int error, const char* description)
{
    HZ_CORE_ERROR("GLFW Error: ({0}): {1}", error, description);
}

Window* Window::Create(const WindowProps& props)
{
    return new MacWindow(props);
}

MacWindow::MacWindow(const WindowProps& props)
{
    Init(props);
}

MacWindow::~MacWindow()
{
    Shutdown();
}

void MacWindow::Init(const WindowProps& props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    
    HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
    
    if (!s_GLFWInitialzed)
    {
        int success = glfwInit();
        HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);
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
    
    m_Context =  new OpenGLContext(m_Window);
    
    m_Context->Init();
    
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
    
    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;
        
        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });
    
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });
    
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        
        switch (action) {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
                
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            default:
                break;
        }
    });
    
    glfwSetCharCallback(m_Window, [](GLFWwindow* window, u_int32_t keycode)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });
    
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        
        switch (action) {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            default:
                break;
        }
    });
    
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        
        MouseScrolledEvent event((float) xoffset, (float) yoffset);
        data.EventCallback(event);
    });
    
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        
        MouseMovedEvent event((float) xPos, (float) yPos);
        data.EventCallback(event);
    });
    
    
}

void MacWindow::OnUpdate()
{
    glfwPollEvents();
    m_Context->SwapBuffers();
}

void MacWindow::SetVSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
    m_Data.VSync = enabled;
}

bool MacWindow::IsVSync() const
{
    return m_Data.VSync;
}

void MacWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

}
