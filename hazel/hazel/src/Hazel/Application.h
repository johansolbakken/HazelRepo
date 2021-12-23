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
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"

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
		
		// ---- Singleton pattern ----------------------------------
		inline static Application& Get() { return *s_Instance; }
		// ---------------------------------------------------------
		
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		
		// Example: Creating a simple triangle
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		
	private:
		static Application* s_Instance;
	};
	
	// ---- To be defines by client --------
	Application* CreateApplication();
	// -------------------------------------
}
