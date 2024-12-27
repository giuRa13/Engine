#include <Engine.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public ENGINE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//ENGINE_APP_INFO("ExampleLayer::Update");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("test test");
		ImGui::End();
	}

	void OnEvent(ENGINE::Event& event) override
	{
		//ENGINE_APP_DEBUG("{0}", event.ToString());
	}
};



class Sandbox : public ENGINE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

ENGINE::Application* ENGINE::CreateApplication()
{
	return new Sandbox();
}