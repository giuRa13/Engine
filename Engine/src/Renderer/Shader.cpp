#include "Shader.hpp"
#include "Renderer.hpp"
#include "OpenGL/OpenGLShader.hpp"
#include "../Log.hpp"

namespace ENGINE 
{

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ENGINE_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		return nullptr;
	}

}