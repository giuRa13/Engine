#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "OpenGL/OpenGLVertexArray.hpp"
#include "../Log.hpp"


namespace ENGINE 
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    ENGINE_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}
		return nullptr;
	}

}