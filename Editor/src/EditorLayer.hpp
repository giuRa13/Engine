#pragma once

#include <Engine.hpp>
#include <Renderer/EditorCamera.hpp>
#include <filesystem>

namespace ENGINE
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;


	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void OnOverlayRender();

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();
		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);
		void OnScenePlay();
		void OnSceneStop();
		void OnDuplicateEntity();

		void UI_Toolbar();

	private:
		OrthographicCameraController m_CameraController;

		// Temp
		//Ref<VertexArray> m_SquareVA;
		//Ref<Shader> m_FlatColorShader;
		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_IconPlay, m_IconStop;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec3 m_SquarePosition = { 0.5f, -0.6f, 0.1f };
		float m_SquareMoveSpeed = 2.0f;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;
		EditorCamera m_EditorCamera;
		Entity m_SquareEntity;//entt::entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		bool m_PrimaryCamera = true;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
		Entity m_HoveredEntity;
		

		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec4 m_ClearColor = { 0.1f, 0.1f, 0.1f, 1 };
		bool showDemo = false;
		int m_GizmoType = -1;
		bool m_ShowPhysicsColliders = false;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState m_SceneState = SceneState::Edit;
	};
}