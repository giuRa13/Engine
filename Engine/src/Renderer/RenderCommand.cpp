#include "RenderCommand.hpp"
#include "OpenGL/OpenGLRendererAPI.hpp"


namespace ENGINE 
{
	//RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}