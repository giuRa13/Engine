#pragma once

#include <Engine.hpp>


class Sandbox2D : public ENGINE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ENGINE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ENGINE::Event& e) override;


private:
	ENGINE::OrthographicCameraController m_CameraController;

	// Temp
	ENGINE::Ref<ENGINE::VertexArray> m_SquareVA;
	ENGINE::Ref<ENGINE::Shader> m_FlatColorShader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
