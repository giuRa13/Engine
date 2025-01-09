#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window.hpp"
#include "Layers/LayerStack.hpp"
#include "Layers/ImGuiLayer.hpp"


namespace ENGINE 
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;
		const char* operator[](int index) const
		{
			//ENGINE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class Application
	{
	public:
		Application(const std::string& name = "Engine App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);
		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }


	private:
		bool OnWindowClose(WindowClosedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		ApplicationCommandLineArgs m_CommandLineArgs;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;

	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);

}