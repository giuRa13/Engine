#pragma once

#include "RenderCommand.hpp"
#include "OrthographicCamera.hpp"
#include "Shader.hpp"


namespace ENGINE 
{

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		//static SceneData* m_pSceneData;
		static Scope<SceneData> m_pSceneData;
	};

}