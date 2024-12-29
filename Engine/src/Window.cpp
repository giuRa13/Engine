#include "Window.hpp"
#include "WindowGLFW.hpp"


namespace ENGINE
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowGLFW>(props);
	}

}