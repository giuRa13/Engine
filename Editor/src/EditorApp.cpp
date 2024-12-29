#include <Engine.hpp>
#include <Entry.hpp>
#include "EditorLayer.hpp"


namespace ENGINE 
{
	
	class Editor : public Application
	{
	public:
		Editor()
			: Application("Engine Editor")
		{
			PushLayer(new EditorLayer());
		}
		~Editor()
		{
		}
	};
	
	Application* CreateApplication()
	{
		return new Editor();
	}
}