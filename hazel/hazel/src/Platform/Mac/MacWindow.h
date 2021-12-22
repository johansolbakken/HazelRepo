#pragma once

#include "Hazel/Window.h"

#include "Platform/OpenGL/OpenGLContext.h"

struct GLFWwindow;

namespace Hazel {
	
	class MacWindow : public Window
	{
	public:
		MacWindow(const WindowProps& props);
		virtual ~MacWindow();
		
		void OnUpdate() override;
		
		inline unsigned int GetWidth() const override {return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		inline virtual void* GetNativeWindow() const override { return m_Window; }
		
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		
		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			
			EventCallbackFn EventCallback;
		};
		
		WindowData m_Data;
	};
	
}
