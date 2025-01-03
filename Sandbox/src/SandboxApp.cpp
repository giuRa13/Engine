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

	ENGINE::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = ENGINE::Framebuffer::Create(fbSpec);
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

	m_Framebuffer->Bind();
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

	m_Framebuffer->Unbind();
}

void Sandbox2D::OnEvent(ENGINE::Event& e)
{
	m_CameraController.OnEvent(e);
}


void Sandbox2D::OnImGuiRender()
{
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
	// all active windows docked into it will lose their parent and become undocked.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace ////////////////////////////////////
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) ENGINE::Application::Get().Close();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Demo"))
		{
			if (ImGui::MenuItem("Open")) showDemo = true;

			if (ImGui::MenuItem("Close")) showDemo = false;
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	if (showDemo)
		ImGui::ShowDemoWindow(&showDemo);


	//////////////////////////////////////////////
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

	// Viewport ////////////////////////////////////////////////
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");

	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();
	ENGINE::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
  
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((uint32_t)(void*)textureID, ImVec2{ m_ViewportSize.x,  m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}
