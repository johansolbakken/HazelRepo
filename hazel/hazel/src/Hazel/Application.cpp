//
//  Application.cpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include "hzpch.h"

#include "Application.hpp"
#include "Input.h"

#include <Glad/glad.h>

namespace Hazel {

// Singleton instance
Application* Application::s_Instance = nullptr;

Application::Application() {
    HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {
    
}

void Application::PushLayer(Layer *layer) {
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer *overlay) {
    m_LayerStack.PushOverlay(overlay);
}

void Application::OnEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClosed));
    
    // Going backwards to give the top layer the event
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled())
            break;
    }
}

void Application::Run() {
    while (m_Running) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (Layer* layer : m_LayerStack)
            layer->OnUpdate();
        
        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClosed(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

}
