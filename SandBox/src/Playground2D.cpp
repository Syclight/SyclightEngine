#include "Playground2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
		{
			Stop();
		}
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult peofileResult) { m_ProfileResults.push_back(peofileResult); })

Playground2D::Playground2D()
	:Layer("Playground2D"),
	m_CameraController(ASPECT_RATIO)
{
}

void Playground2D::OnAttach()
{
	m_Texture = syc::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Playground2D::OnDetach()
{
}

void Playground2D::OnUpdate(syc::Timestep timestep)
{
	PROFILE_SCOPE("Playground2D::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}
	

	// Render
	{
		PROFILE_SCOPE("Renderer Prep");
		syc::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1);
		syc::RenderCommand::Clear();
	}
	
	{
		PROFILE_SCOPE("Renderer Draw");
		syc::Renderer2D::BeginScene(m_CameraController.GetCamera());
		syc::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		syc::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
		syc::Renderer2D::EndScene();
	}

	//std::dynamic_pointer_cast<syc::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<syc::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Playground2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Solor", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char lable[50];
		strcpy_s(lable, result.Name);
		strcat_s(lable, " %.3fms");
		ImGui::Text(lable, result.Time);
	}
	m_ProfileResults.clear();
	ImGui::End();
}

void Playground2D::OnEvent(syc::Event& event)
{
	m_CameraController.OnEvent(event);
}
