#include <Engine.hpp>
#include <Core.hpp>
#include "SandboxApp.hpp"
#include <Entry.hpp>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public ENGINE::Layer
{

public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true), m_SquarePosition(0.0f)
	{
		////////////////////////////////////////////////////////////
		m_VertexArray = ENGINE::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};
		ENGINE::Ref<ENGINE::VertexBuffer> vertexBuffer;
		vertexBuffer = ENGINE::VertexBuffer::Create(vertices, sizeof(vertices));
		ENGINE::BufferLayout layout = {
			{ ENGINE::ShaderDataType::Float3, "a_Position" },
			{ ENGINE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		ENGINE::Ref<ENGINE::IndexBuffer> indexBuffer;
		indexBuffer = ENGINE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				//gl_Position = vec4(a_Position, 1.0);	
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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
		m_Shader = ENGINE::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		////////////////////////////////////////////////////////////

		m_SquareVA = ENGINE::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f
		};
		ENGINE::Ref<ENGINE::VertexBuffer> squareVB;
		squareVB = ENGINE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ENGINE::ShaderDataType::Float3, "a_Position" },
			{ ENGINE::ShaderDataType::Float2, "a_TexCoord" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ENGINE::Ref<ENGINE::IndexBuffer> squareIB;
		squareIB = ENGINE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string flatColorShaderVertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				//gl_Position = vec4(a_Position, 1.0);	
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				//color = vec4(0.2, 0.3, 0.8, 1.0);
				color = vec4(u_Color, 1.0);
			}
		)";
		m_FlatColorShader = ENGINE::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		////////////////////////////////////////////////////////////

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = ENGINE::Texture2D::Create("assets/textures/Checkerboard.png");
		//m_FaceTexture = ENGINE::Texture2D::Create("assets/textures/awesomeface.png");
		std::dynamic_pointer_cast<ENGINE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ENGINE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}


	void OnUpdate(ENGINE::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (ENGINE::Input::IsKeyPressed(ENGINE_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		///////////////////////////////////////////////////////////
		ENGINE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ENGINE::RenderCommand::Clear();

		ENGINE::Renderer::BeginScene(m_CameraController.GetCamera());
		{
			auto textureShader = m_ShaderLibrary.Get("Texture");
			m_Texture->Bind();
			ENGINE::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			//m_FaceTexture->Bind();
			//ENGINE::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			std::dynamic_pointer_cast<ENGINE::OpenGLShader>(m_FlatColorShader)->Bind();
			std::dynamic_pointer_cast<ENGINE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					/*if (x % 2 == 0)
						std::dynamic_pointer_cast<ENGINE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_RedColor);
					else
						std::dynamic_pointer_cast<ENGINE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);*/
					ENGINE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
				}
			}

			std::dynamic_pointer_cast<ENGINE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_RedColor);
			glm::mat4 squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
			glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), m_SquarePosition) * squareScale;
			ENGINE::Renderer::Submit(m_FlatColorShader, m_SquareVA, squareTransform);
			
			ENGINE::Renderer::Submit(m_Shader, m_VertexArray);
		}
		ENGINE::Renderer::EndScene();
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");

		ImGui::Text("test test");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(ENGINE::Event& event) override
	{
		//ENGINE_APP_DEBUG("{0}", event.ToString());

		m_CameraController.OnEvent(event);
	}


private:
	ENGINE::ShaderLibrary m_ShaderLibrary;
	ENGINE::Ref<ENGINE::Shader> m_Shader;
	ENGINE::Ref<ENGINE::VertexArray> m_VertexArray;
	ENGINE::Ref<ENGINE::Shader> m_FlatColorShader;
	ENGINE::Ref<ENGINE::VertexArray> m_SquareVA;
	ENGINE::Ref<ENGINE::Texture2D> m_Texture, m_FaceTexture;

	ENGINE::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f};
	glm::vec3 m_RedColor = { 0.8f, 0.2f, 0.3f };
};



/*class Sandbox : public ENGINE::Application
{
public:
	Sandbox()
		:Application("Sandbox")
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

ENGINE::Application* ENGINE::CreateApplication()
{
	return new Sandbox();
}*/


class Sandbox : public ENGINE::Application
{
public:
	Sandbox(const ENGINE::ApplicationSpecification& specification)
		: ENGINE::Application(specification)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

ENGINE::Application* ENGINE::CreateApplication(ENGINE::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Editor";
	spec.CommandLineArgs = args;
	return new Sandbox(spec);
}