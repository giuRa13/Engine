#pragma once

#include <Engine.hpp>

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
		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<ENGINE::VertexArray> m_SquareVA;
		Ref<ENGINE::Shader> m_FlatColorShader;
		Ref<ENGINE::Texture2D> m_CheckerboardTexture;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec3 m_SquarePosition = { 0.5f, -0.6f, 0.1f };
		float m_SquareMoveSpeed = 2.0f;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;//entt::entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		bool m_PrimaryCamera = true;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		

		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec4 m_ClearColor = { 0.1f, 0.1f, 0.1f, 1 };
		bool showDemo = false;
		int m_GizmoType = -1;
	};
}