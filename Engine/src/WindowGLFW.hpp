#pragma once

#include "Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ENGINE
{

	class WindowGLFW : public Window
	{
	public:
		WindowGLFW(const WindowProps& props);
		virtual ~WindowGLFW();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		virtual void* GetNativeWindow() const { return m_Window; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;


	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;

	};
}
