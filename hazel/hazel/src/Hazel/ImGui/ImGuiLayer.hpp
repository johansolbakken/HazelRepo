//
//  ImGuiLayer.hpp
//  Hazel
//
//  Created by Johan Solbakken on 13/12/2021.
//

#pragma once

#include "Hazel/Layer.hpp"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();
    
    void OnUpdate() override;
    void OnEvent(Event& event) override;
    void OnAttach() override;
    void OnDetach() override;
private:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(MouseMovedEvent& e);
    bool OnMouseScrolledEvent(MouseScrolledEvent& e);
    
    bool OnKeyPressedEvent(KeyPressedEvent& e);
    bool OnKeyReleasedEvent(KeyReleasedEvent& e);
    bool OnKeyTypedEvent(KeyTypedEvent& e);
    
    bool OnWindowResizedEvent(WindowResizeEvent& e);
    
private:
    float m_Time = 0.0f;
};

}
