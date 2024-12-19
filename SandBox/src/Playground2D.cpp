#include "sycpch.h"
#include "Playground2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Playground2D::Playground2D()
	:Layer("Playground2D"),
	m_CameraController(ASPECT_RATIO)
{
}

void Playground2D::OnAttach()
{
	SYC_PROFILE_FUNCTION();

	m_Texture = syc::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Playground2D::OnDetach()
{
	SYC_PROFILE_FUNCTION();
}

void Playground2D::OnUpdate(syc::Timestep timestep)
{
	SYC_PROFILE_FUNCTION();

	// Update
	{
		SYC_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}
	

	// Render
	syc::Renderer2D::ResetStats();
	{
		SYC_PROFILE_SCOPE("Renderer Prep");

		syc::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1);
		syc::RenderCommand::Clear();
	}
	
	{
		static float rotation = 0.0f;
		rotation += timestep * 5.0f;

		SYC_PROFILE_SCOPE("Renderer Draw");

		syc::Renderer2D::BeginScene(m_CameraController.GetCamera());

		syc::Renderer2D::DrawRotateQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		syc::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		syc::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 10.0f);
		syc::Renderer2D::DrawRotateQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture, 20.0f);
		/*syc::Renderer2D::EndScene();

		syc::Renderer2D::BeginScene(m_CameraController.GetCamera());*/
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				syc::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		syc::Renderer2D::EndScene();

	}

	//std::dynamic_pointer_cast<syc::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<syc::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Playground2D::OnImGuiRender()
{
	SYC_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = syc::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls %d", stats.DrawCalls);
	ImGui::Text("Quads %d", stats.QuadCount);
	ImGui::Text("Vertices %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void Playground2D::OnEvent(syc::Event& event)
{
	m_CameraController.OnEvent(event);
}
