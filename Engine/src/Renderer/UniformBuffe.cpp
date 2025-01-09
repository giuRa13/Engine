#include "UniformBuffer.hpp"
#include "Renderer.hpp"
#include "OpenGL/OpenGLUniformBuffer.hpp"


namespace ENGINE 
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;//HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}
		//HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}