#pragma once

#include "Layer.hpp"


namespace ENGINE 
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event) override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();


	private:
	};

}
