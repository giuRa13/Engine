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
		void BlockEvents(bool block) { m_BlockEvents = block; }

		virtual void OnImGuiRender() override;

		void Begin();
		void End();


	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};

}
