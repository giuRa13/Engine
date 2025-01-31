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

	static float rotation = 0.0f;
	rotation += ts * 50.0f;


	// Render
	ENGINE::Renderer2D::ResetStats();

	ENGINE::RenderCommand::SetClearColor(m_ClearColor);//{ 0.1f, 0.1f, 0.1f, 1 }
	ENGINE::RenderCommand::Clear();

	ENGINE::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		ENGINE::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f});
		ENGINE::Renderer2D::DrawQuad(m_SquarePosition, { 0.5f, 0.75f }, m_SquareColor);
		ENGINE::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 15.0f, 15.0f }, m_CheckerboardTexture, 7.5f, { 1.0f, 0.8f, 0.8f, 1.0f });
		ENGINE::Renderer2D::DrawRotatedQuad({ -1.5f, 1.0f }, { 0.5f, 0.5f }, rotation, { 1.0f, 0.6f, 0.3f, 1.0f });

	}
	ENGINE::Renderer2D::EndScene();

	ENGINE::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				ENGINE::Renderer2D::DrawQuad({ x, y, -0.2f }, { 0.45f, 0.45f }, color);
			}
		}
	}
	ENGINE::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(ENGINE::Event& e)
{
	m_CameraController.OnEvent(e);
}


void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = ENGINE::Renderer2D::GetStats();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(66, 150, 240, 240));
	ImGui::Text("Renderer2D Stats:");
	ImGui::PopStyleColor();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::NewLine();
	ImGui::Separator();
	ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_ClearColor));
	ImGui::SameLine();
	if (ImGui::Button("Original"))
		m_ClearColor = { 0.1f, 0.1f, 0.1f, 1 };
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::NewLine();
	ImGui::Separator();
	uint32_t texID = m_CheckerboardTexture->GetRendererID();
	ImGui::Image((uint32_t)(void*)texID, ImVec2{ 256.0f, 256.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
}
