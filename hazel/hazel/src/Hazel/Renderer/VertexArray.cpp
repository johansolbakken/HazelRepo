#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None: 	HZ_CORE_ASSERT(false, "Does not support RendererAPI::None"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}
		
		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	}
	
}
