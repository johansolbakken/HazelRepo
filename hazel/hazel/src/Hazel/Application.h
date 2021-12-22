//
//  Application.hpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

namespace Hazel
{
	
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		
		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		inline Window& GetWindow() { return *m_Window; }
		
		// Singleton pattern
		inline static Application& Get() { return *s_Instance; }
		
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		
		u_int32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		
	private:
		static Application* s_Instance;
	};
	
	// To be defined in client
	Application* CreateApplication();
	
}
