//
//  ImGuiLayer.cpp
//  Hazel
//
//  Created by Johan Solbakken on 13/12/2021.
//

#include "hzpch.h"
#include "ImGuiLayer.hpp"

#include <imgui.h>

#define IMGUI_IMPL_API
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "Hazel/Application.hpp"

namespace Hazel {

ImGuiLayer::ImGuiLayer() : Layer("ImGui layer")
{
    
}

ImGuiLayer::~ImGuiLayer()
{
    
}

void ImGuiLayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable keyboard controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // Enable docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewPortsNoMerge;
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    
    // When viewports are enabled we tweak WindowRouding so platforms window look identical
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    
    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
    
    // Setup platform / rendering bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());
    
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiLayer::OnImGuiRender() {
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

}
