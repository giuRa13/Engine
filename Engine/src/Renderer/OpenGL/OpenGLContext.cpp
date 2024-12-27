#include "OpenGLContext.hpp"
#include <Log.hpp>


namespace ENGINE
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			ENGINE_CORE_ERROR("Failed to init Glad");
			glfwTerminate();
		}

		ENGINE_CORE_DEBUG("OpenGL Info:\n  \tVendor: \t{}\n  \tRenderer:\t{}\n  \tVersion:\t{}",
			(const char*)glGetString(GL_VENDOR),
			(const char*)glGetString(GL_RENDERER),
			(const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}