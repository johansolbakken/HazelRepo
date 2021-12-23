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
		virtual ~Shader() {}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}
