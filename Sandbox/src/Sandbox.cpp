#include <Engine.hpp>
#include <memory>
#include <imgui/imgui.h>

class ExampleLayer : public ENGINE::Layer
{

public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), //(Aspect ratio 16:9)
		m_CameraPosition(0.0f)
	{
		////////////////////////////////////////////////////////////
		m_VertexArray.reset(ENGINE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<ENGINE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ENGINE::VertexBuffer::Create(vertices, sizeof(vertices)));
		ENGINE::BufferLayout layout = {
			{ ENGINE::ShaderDataType::Float3, "a_Position" },
			{ ENGINE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<ENGINE::IndexBuffer> indexBuffer;
		indexBuffer.reset(ENGINE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				//gl_Position = vec4(a_Position, 1.0);	
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(new ENGINE::Shader(vertexSrc, fragmentSrc));
		////////////////////////////////////////////////////////////

		m_SquareVA.reset(ENGINE::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<ENGINE::VertexBuffer> squareVB;
		squareVB.reset(ENGINE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ENGINE::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ENGINE::IndexBuffer> squareIB;
		squareIB.reset(ENGINE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueShaderVertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				//gl_Position = vec4(a_Position, 1.0);	
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";
		std::string blueShaderFragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new ENGINE::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
		////////////////////////////////////////////////////////////
	}


	void OnUpdate(ENGINE::Timestep ts) override
	{
		if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		///////////////////////////////////////////////////////////
		ENGINE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ENGINE::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		ENGINE::Renderer::BeginScene(m_Camera);
		{
			ENGINE::Renderer::Submit(m_BlueShader, m_SquareVA);
			ENGINE::Renderer::Submit(m_Shader, m_VertexArray);
		}
		ENGINE::Renderer::EndScene();
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("test test");
		ImGui::End();
	}

	void OnEvent(ENGINE::Event& event) override
	{
		//ENGINE_APP_DEBUG("{0}", event.ToString());
	}


private:
	std::shared_ptr<ENGINE::Shader> m_Shader;
	std::shared_ptr<ENGINE::VertexArray> m_VertexArray;
	std::shared_ptr<ENGINE::Shader> m_BlueShader;
	std::shared_ptr<ENGINE::VertexArray> m_SquareVA;

	ENGINE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;
};



class Sandbox : public ENGINE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

ENGINE::Application* ENGINE::CreateApplication()
{
	return new Sandbox();
}