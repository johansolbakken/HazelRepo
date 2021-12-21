//
//  SandboxApp.cpp
//  Sandbox
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include <Hazel.h>

#include <imgui.h>

class ExampleLayer : public Hazel::Layer {
public:
    ExampleLayer() : Layer("Example") {
    }
    
    void OnUpdate() override {
        if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
            HZ_INFO("Tab key pressed!");
    }
    
    virtual void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello, World!");
        ImGui::End();
    }
    
    void OnEvent(Hazel::Event& event) override {
        //HZ_TRACE("{0}", event);
    }
};

class Sandbox : public Hazel::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    
    ~Sandbox() {
        
    }
};

Hazel::Application* Hazel::CreateApplication() {
    return new Sandbox();
}
