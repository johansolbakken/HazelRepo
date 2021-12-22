//
//  Shader.cpp
//  Hazel
//
//  Created by Johan Solbakken on 22/12/2021.
//

#include "hzpch.h"
#include "Shader.h"

#include <Glad/glad.h>

namespace Hazel
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar *source = (const GLchar*) vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);
		
		int32_t isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
			
			return;
		}
		
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = (const GLchar*) vertexSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);
		
		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			
			glDeleteShader(fragmentShader);
			
			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Fragment shader compilation failure!");
			
			return;
		}
		
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		
		glLinkProgram(m_RendererID);
		
		int32_t isLinked;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
			
			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Program linking failure!");
			
			return;
		}
		
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}
	
	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}
	
	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}
