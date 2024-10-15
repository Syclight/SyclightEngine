#include <Syclight.h>

#include "imgui/imgui.h"

class ExampleLayer : public syc::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(syc::VertexArray::Create());

		float32t vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<syc::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(syc::VertexBuffer::Create(vertices, sizeof(vertices)));

		syc::BufferLayout layout = {
			{ syc::ShaderDataType::Float3, "a_Position" },
			{ syc::ShaderDataType::Float4, "a_Color" }
			//{ ShaderDataType::Float3, "a_Normal" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVerrtexBuffer(vertexBuffer);

		syc::uint32 indices[3] = { 0, 1, 2 };
		std::shared_ptr<syc::IndexBuffer> indexBuffer;
		indexBuffer.reset(syc::IndexBuffer::Create(indices, sizeof(indices) / sizeof(syc::uint32)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(syc::VertexArray::Create());

		float32t squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<syc::VertexBuffer> SquareVB;
		SquareVB.reset(syc::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		syc::BufferLayout SquareLayout = {
			{ syc::ShaderDataType::Float3, "a_Position" }
		};
		SquareVB->SetLayout(SquareLayout);
		m_SquareVA->AddVerrtexBuffer(SquareVB);

		syc::uint32 SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<syc::IndexBuffer> SquareIB;
		SquareIB.reset(syc::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(syc::uint32)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		std::string vertexShader = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;			
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new syc::Shader(vertexShader, fragmentShader));

		std::string vertexShader2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;			

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_SquareShader.reset(new syc::Shader(vertexShader2, fragmentShader2));
	}

	void OnUpdate(syc::Timestep timestep) override
	{

		if (syc::Input::IsKeyPressed(SYC_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		else if (syc::Input::IsKeyPressed(SYC_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}

		if (syc::Input::IsKeyPressed(SYC_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}
		else if (syc::Input::IsKeyPressed(SYC_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}

		if (syc::Input::IsKeyPressed(SYC_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		}
		if (syc::Input::IsKeyPressed(SYC_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		}

		syc::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1);
		syc::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		syc::Renderer::BeginScene(m_Camera);

		syc::Renderer::Submit(m_SquareShader, m_SquareVA);
		syc::Renderer::Submit(m_Shader, m_VertexArray);

		syc::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hi! This is Syclight Engine.");
		ImGui::End();
	}

	void OnEvent(syc::Event& e) override
	{
		/*syc::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<syc::KeyPressedEvent>(SYC_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));*/
	}

	/*bool OnKeyPressedEvent(syc::KeyPressedEvent& e)
	{
		

		return false;
	}*/

private:
	std::shared_ptr<syc::VertexArray> m_VertexArray;
	std::shared_ptr<syc::Shader> m_Shader;

	std::shared_ptr<syc::VertexArray> m_SquareVA;
	std::shared_ptr<syc::Shader> m_SquareShader;

	syc::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public syc::Application
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

syc::Application* syc::CreateApplication()
{
	return new Sandbox();
}