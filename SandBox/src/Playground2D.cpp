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
	{
		SYC_PROFILE_SCOPE("Renderer Prep");

		syc::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1);
		syc::RenderCommand::Clear();
	}
	
	{
		SYC_PROFILE_SCOPE("Renderer Draw");

		syc::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//syc::Renderer2D::DrawRotateQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		syc::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		syc::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);
		syc::Renderer2D::EndScene();
	}

	//std::dynamic_pointer_cast<syc::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<syc::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Playground2D::OnImGuiRender()
{
	SYC_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	/*ImGui::ColorEdit4("Square Solor", glm::value_ptr(m_SquareColor));*/

	/*for (auto& result : m_ProfileResults)
	{
		char lable[50];
		strcpy_s(lable, "%.3fms ");
		strcat_s(lable, result.Name);
		ImGui::Text(lable, result.Time);
	}
	m_ProfileResults.clear();*/
	ImGui::End();
}

void Playground2D::OnEvent(syc::Event& event)
{
	m_CameraController.OnEvent(event);
}
