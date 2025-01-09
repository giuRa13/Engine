#include <Engine.hpp>
#include <Entry.hpp>
#include "EditorLayer.hpp"


namespace ENGINE 
{
	
	class Editor : public Application
	{
	public:
		Editor(ApplicationCommandLineArgs args)
			: Application("Editor", args)
		{
			PushLayer(new EditorLayer());
		}
		~Editor()
		{
		}
	};
	
	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Editor(args);
	}

}