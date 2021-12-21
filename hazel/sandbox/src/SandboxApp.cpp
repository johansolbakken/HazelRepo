//
//  SandboxApp.cpp
//  Sandbox
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include <Hazel.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Hazel::Layer {
public:
    ExampleLayer() : Layer("Example") {
    }
    
    void OnUpdate() override {
        if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
            HZ_INFO("Tab key pressed!");
    }
    
    void OnEvent(Hazel::Event& event) override {
        //HZ_TRACE("{0}", event);
    }
};

class Sandbox : public Hazel::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new Hazel::ImGuiLayer());
    }
    
    ~Sandbox() {
        
    }
};

Hazel::Application* Hazel::CreateApplication() {
    return new Sandbox();
}
