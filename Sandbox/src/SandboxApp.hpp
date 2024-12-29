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
	ENGINE::Ref<ENGINE::Texture2D> m_CheckerboardTexture;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec3 m_SquarePosition = { 0.5f, -0.6f, 0.1f};
	float m_SquareMoveSpeed = 2.0f;

	ENGINE::Ref<ENGINE::Framebuffer> m_Framebuffer;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	bool m_ViewportFocused = false, m_ViewportHovered = false;
	glm::vec4 m_ClearColor = { 0.1f, 0.1f, 0.1f, 1 };
	bool showDemo = false;
};
