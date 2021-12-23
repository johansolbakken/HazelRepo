//
//  Shader.cpp
//  Hazel
//
//  Created by Johan Solbakken on 22/12/2021.
//

#include "hzpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::None: 	HZ_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::OpenGL: 	return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		
		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
