#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "OpenGL/OpenGLVertexArray.hpp"
#include "../Log.hpp"


namespace ENGINE 
{

	//VertexArray* VertexArray::Create()
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ENGINE_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}
		return nullptr;
	}

}