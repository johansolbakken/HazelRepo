//
//  ImGuiLayer.hpp
//  Hazel
//
//  Created by Johan Solbakken on 13/12/2021.
//

#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;
    
    void Begin();
    void End();
};

}
