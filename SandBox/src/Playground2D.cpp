#include "sycpch.h"
#include "Playground2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const syc::int32 MapWidth = 50;
static const syc::int32 MapHeight = 50;
static const syc::char8* MapTiles =
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo"
"oooooooooooooooooooooooooooooooooooooooooooooooooo";


Playground2D::Playground2D()
	:Layer("Playground2D"),
	m_CameraController(ASPECT_RATIO)
{
}

void Playground2D::OnAttach()
{
	SYC_PROFILE_FUNCTION();

	m_Texture = syc::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = syc::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
	m_TextureStairs = syc::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128.0f, 128.0f });
	m_TextureBarrel = syc::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128.0f, 128.0f });
	m_TextureTree = syc::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128.0f, 128.0f }, {1, 2});

	//初始化粒子系统
	m_Particle.ColorBegin = { 0.8f, 0.8f, 0.2f, 1.0f };
	m_Particle.ColorEnd = { 0.2f, 0.8f, 0.8f, 1.0f };
	m_Particle.SizeBegin = 0.3f, m_Particle.SizeVariation = 0.1f; m_Particle.SizeEnd = 0.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.LifeTime = 5.0f;
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
}

void Playground2D::OnDetach()
{
	SYC_PROFILE_FUNCTION();
}

void Playground2D::OnUpdate(syc::Timestep timestep)
{
	SYC_PROFILE_FUNCTION();

	m_FrameDeltaTime = timestep;

	m_FrameCount++;
	m_FPSTimeCounter += m_FrameDeltaTime;
	if (m_FPSTimeCounter >= 1.0) {
		m_FPS = m_FrameCount / m_FPSTimeCounter;
		m_FPSTimeCounter = 0.0;
		m_FrameCount = 0;
	}

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
	
#if 0
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
#endif

	if (syc::Input::IsMouseButtonPressed(SYC_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = syc::Input::GetMousePosition();
		auto width = syc::Application::Get().GetWindow().GetWidth();
		auto height = syc::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (size_t i = 0; i < 5; i++)
		{
			m_ParticleSystem.Emit(m_Particle);
		}
	}

	m_ParticleSystem.OnUpdate(timestep);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	syc::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_SpriteSheet);
	/*for (size_t i = 0; i < 180; i++)
	{
		for (size_t j = 0; j < 180; j++)
		{
			syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
		}
	}*/
	syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
	syc::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureBarrel);
	syc::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, m_TextureTree);
	syc::Renderer2D::EndScene();

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
	ImGui::Text("Frame Time %fms (%0.5ffps)", m_FrameDeltaTime * 1000, m_FPS);

	ImGui::End();
}

void Playground2D::OnEvent(syc::Event& event)
{
	m_CameraController.OnEvent(event);
}
