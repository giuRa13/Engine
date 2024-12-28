#include "Renderer.hpp"

namespace ENGINE 
{
	Renderer::SceneData* Renderer::m_pSceneData = new Renderer::SceneData;


	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_pSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}
	
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_pSceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}