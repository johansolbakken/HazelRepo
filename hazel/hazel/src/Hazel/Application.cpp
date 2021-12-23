//
//  Application.cpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include "hzpch.h"

#include "Application.h"
#include "Input.h"

#include <Glad/glad.h>

namespace Hazel
{
	// ---- Singleton instance ---------------------------------
	Application* Application::s_Instance = nullptr;
	// ---------------------------------------------------------
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float: 	return GL_FLOAT;
			case ShaderDataType::Float2: 	return GL_FLOAT;
			case ShaderDataType::Float3: 	return GL_FLOAT;
			case ShaderDataType::Float4: 	return GL_FLOAT;
			case ShaderDataType::Mat3: 		return GL_FLOAT;
			case ShaderDataType::Mat4: 		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2: 		return GL_INT;
			case ShaderDataType::Int3: 		return GL_INT;
			case ShaderDataType::Int4: 		return GL_INT;
			case ShaderDataType::Bool: 		return GL_BOOL;
		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}
	
	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();
		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.7f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.7f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.7f, 1.0f
		};
		
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();
		
		// Creating a layout
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};
			
			m_VertexBuffer->SetLayout(layout);
		}
		
		// Enabling the layout
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
								  index,
								  element.GetComponentCount(),
								  ShaderDataTypeToOpenGLBaseType(element.Type),
								  element.Normalized ? GL_TRUE : GL_FALSE,
								  layout.GetStride(),
								  (const void*) element.Offset
								  );
			index++;
		}
		
		uint32_t indices[3] = {
			0, 1, 2
		};
		
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_IndexBuffer->Bind();
		
		std::string vertexSrc = R"(
		#version 410 core
		
		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;
		
		out vec4 v_Color;
		
		void main()
		{
		gl_Position = vec4(a_Position, 1.0);
		v_Color = a_Color;
		}
		)";
		
		std::string fragmentSrc = R"(
		#version 410 core
		
		in vec4 v_Color;
		
		out vec4 color;
		
		void main()
		{
		color = v_Color;
		}
		)";
		
		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		
		m_Shader->Unbind();
	}
	
	Application::~Application()
	{}
	
	void Application::PushLayer(Layer *layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	
	void Application::PushOverlay(Layer *overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
	
	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClosed));
		
		// Going backwards to give the top layer the event
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			// Render imgui
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}
	
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
}
