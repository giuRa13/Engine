#include "RenderCommand.hpp"
#include "OpenGL/OpenGLRendererAPI.hpp"


namespace ENGINE 
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}