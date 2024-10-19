#include "Syclight.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Syclight/Renderer/Shader.h"


class ExampleLayer : public syc::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		m_CameraController(16.0f / 9.0f)
	{
		m_VertexArray.reset(syc::VertexArray::Create());

		F32 vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		syc::Ref<syc::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(syc::VertexBuffer::Create(vertices, sizeof(vertices)));

		syc::BufferLayout layout = {
			{ syc::ShaderDataType::Float3, "a_Position" },
			{ syc::ShaderDataType::Float4, "a_Color" }
			//{ ShaderDataType::Float3, "a_Normal" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVerrtexBuffer(vertexBuffer);

		syc::uint32 indices[3] = { 0, 1, 2 };
		syc::Ref<syc::IndexBuffer> indexBuffer;
		indexBuffer.reset(syc::IndexBuffer::Create(indices, sizeof(indices) / sizeof(syc::uint32)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(syc::VertexArray::Create());

		F32 squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		syc::Ref<syc::VertexBuffer> SquareVB;
		SquareVB.reset(syc::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		syc::BufferLayout SquareLayout = {
			{ syc::ShaderDataType::Float3, "a_Position" },
			{ syc::ShaderDataType::Float2, "a_TexCoord" }
		};
		SquareVB->SetLayout(SquareLayout);
		m_SquareVA->AddVerrtexBuffer(SquareVB);

		syc::uint32 SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		syc::Ref<syc::IndexBuffer> SquareIB;
		SquareIB.reset(syc::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(syc::uint32)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		std::string vertexShader = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = syc::Shader::Create("shader", vertexShader, fragmentShader);

		std::string vertexShader2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform *vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
            uniform vec3 u_Color;

            uniform vec3 u_lightDir;			

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";
		m_SquareShader = syc::Shader::Create("Square", vertexShader2, fragmentShader2);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = syc::Texture2D::Create("assets/textures/Checkerboard.png");
		m_NanacoTex = syc::Texture2D::Create("assets/textures/nanaco.png");

		std::dynamic_pointer_cast<syc::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<syc::OpenGLShader>(textureShader)->UploadUniforInt("m_TextureShader", 0);
	}

	void OnUpdate(syc::Timestep timestep) override
	{
		// Update
		m_CameraController.OnUpdate(timestep);

		// Render
		syc::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1);
		syc::RenderCommand::Clear();

		syc::Renderer::BeginScene(m_CameraController.GetCamera());

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<syc::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<syc::OpenGLShader>(m_SquareShader)->UploadUniforFloat3("u_Color", m_SquareColor);

		/*syc::MaterialRef material = new syc::Material(m_SquareShader);
		syc::MaterialInstanceRef mi = new syc::MaterialInstanceRef(material);

		mi->Set("u_Color", red);
		squareMesh->SetMaterial(mi);*/

		for (UI32 y = 0; y < 20; y++)
		{
			for (UI32 x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				syc::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		syc::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_NanacoTex->Bind();
		syc::Renderer::Submit(textureShader, m_SquareVA,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// syc::Renderer::Submit(m_Shader, m_VertexArray);

		syc::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Solor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(syc::Event& e) override
	{
		m_CameraController.OnEvent(e);

	/*	if (e.GetEventType() == syc::EventType::WindowResize)
		{
			auto& re = (syc::WindowResizeEvent&)e;

			F32 zoom = (F32)re.GetWidth() / WIND_WIDTH;
			m_CameraController.SetZoomLevel(zoom);
		}*/
	}

	/*bool OnKeyPressedEvent(syc::KeyPressedEvent& e)
	{
		

		return false;
	}*/

private:
	syc::ShaderLibrary m_ShaderLibrary;

	syc::Ref<syc::Shader> m_Shader;
	syc::Ref<syc::VertexArray> m_VertexArray;

	syc::Ref<syc::Shader> m_SquareShader;
	syc::Ref<syc::VertexArray> m_SquareVA;

	syc::Ref<syc::Texture2D> m_Texture, m_NanacoTex;

	syc::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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