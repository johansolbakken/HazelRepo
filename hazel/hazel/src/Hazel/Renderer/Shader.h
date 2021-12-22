//
//  Shader.h
//  Hazel
//
//  Created by Johan Solbakken on 22/12/2021.
//

#pragma once

#include <string>

namespace Hazel
{
	
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		
		void Bind() const;
		void Unbind() const;
		
	private:
		uint32_t m_RendererID;
	};
	
}
