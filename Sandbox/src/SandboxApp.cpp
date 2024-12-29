#include "SandboxApp.hpp"
#include <Renderer/OpenGL/OpenGLShader.hpp>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = ENGINE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}


void Sandbox2D::OnUpdate(ENGINE::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_J))
		m_SquarePosition.x -= m_SquareMoveSpeed * ts;
	else if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_L))
		m_SquarePosition.x += m_SquareMoveSpeed * ts;
	if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_I))
		m_SquarePosition.y += m_SquareMoveSpeed * ts;
	else if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_K))
		m_SquarePosition.y -= m_SquareMoveSpeed * ts;


	// Render
	ENGINE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ENGINE::RenderCommand::Clear();

	ENGINE::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{

		ENGINE::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f});
		ENGINE::Renderer2D::DrawQuad(m_SquarePosition, { 0.5f, 0.75f }, m_SquareColor);

		ENGINE::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);

	}
	ENGINE::Renderer2D::EndScene();
}


void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ENGINE::Event& e)
{
	m_CameraController.OnEvent(e);
}