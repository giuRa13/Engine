#include <Engine.hpp>
#include <Entry.hpp>
#include "EditorLayer.hpp"


namespace ENGINE 
{
	
	class Editor : public Application
	{
	public:
		Editor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
		~Editor()
		{
		}
	};
	
	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Editor App";
		spec.CommandLineArgs = args;
		
		return new Editor(spec);
	}

}