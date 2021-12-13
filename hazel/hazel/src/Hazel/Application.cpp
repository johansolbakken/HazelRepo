//
//  Application.cpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include "hzpch.h"

#include "Application.hpp"

#include <GLFW/glfw3.h>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
    
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
