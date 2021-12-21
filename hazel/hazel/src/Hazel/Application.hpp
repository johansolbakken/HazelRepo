//
//  Application.hpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.hpp"
#include "Window.h"

namespace Hazel {

class Application {
public:
    Application();
    virtual ~Application();
    void Run();
    
    void OnEvent(Event& e);
    
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    
    inline Window& GetWindow() { return *m_Window; }
    
    // Singleton pattern
    inline static Application& Get() {
        return *s_Instance;
    }
    
private:
    bool OnWindowClosed(WindowCloseEvent& e);
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;

private:
    static Application* s_Instance;
};

// To be defined in client
Application* CreateApplication();

}
