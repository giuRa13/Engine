#pragma once

#include "../GraphicsContext.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace ENGINE 
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}