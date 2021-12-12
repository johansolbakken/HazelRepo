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
#include "Window.h"

namespace Hazel {

class Application {
public:
    Application();
    virtual ~Application();
    void Run();
    
    void OnEvent(Event& e);
    
private:
    bool OnWindowClosed(WindowCloseEvent& e);
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// To be defined in client
Application* CreateApplication();

}
