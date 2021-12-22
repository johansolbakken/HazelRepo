//
//  OpenGLContext.cpp
//  Hazel
//
//  Created by Johan Solbakken on 22/12/2021.
//

#include "hzpch.h"
#include "OpenGLContext.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		if (status == 0) HZ_CORE_ERROR("Glad could not load OpenGL");
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");
		
		HZ_CORE_INFO("OpenGL Renderer:");
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
	
}
