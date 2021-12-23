#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel 
{
    class OpenGLVertexArray : public VertexArray
    {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
	
	private:
		uint32_t m_RendererID;
    };
}
