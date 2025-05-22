#include "Game.h"

Game::Game()
	:Layer("Game"),
	m_CameraController(ASPECT_RATIO),
	m_Level()
{
}

void Game::OnAttach()
{
	SYC_PROFILE_FUNCTION();
	// 初始化资源等

	m_Level.Init();

	m_CameraController.SetZoomLevel(10.0f);
	//m_CameraController.SetCameraPos({0.0f, 0.0f, 0.0f});
	m_CameraController.SetCameraPos({52.0f, 15.0f, 0.0f});

	//m_ImGUIAssets.Font = syc::FontManager::GetInstance().LoadFont("assets/fonts/SourceHanSerifSC-Regular.ttf", 20);
	//m_ImGUIAssets.Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 120.0f);
	ImGuiIO& io = ImGui::GetIO();
	m_ImGUIAssets.Font = io.Fonts->AddFontFromFileTTF(
		"assets/fonts/Slideyouran-Regular.ttf",
		120.0f,
		nullptr,
		io.Fonts->GetGlyphRangesChineseFull());

	/*m_SpriteSheet = syc::Texture2D::Create("assets/textures/man_sheet.png");
	m_TextureStairs = syc::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0.0f, 0.0f }, { 16.0f, 16.0f });*/

	m_Audio.playBackgroundMusic("assets/audio/BGM.mp3");
}

void Game::OnDetach()
{
	SYC_PROFILE_FUNCTION();
	// 释放资源等
	m_Audio.stopAudio();
}

void Game::OnUpdate(syc::Timestep timestep)
{
	// 每帧更新

#ifdef _DEBUG
	m_CameraController.OnUpdate(timestep);
#endif // _DEBUG

	syc::OrthographicCameraBounds bounds = m_CameraController.GetBounds();
	
	m_Level.Update(timestep, m_CameraController);
	m_Audio.update();

	syc::Renderer2D::ResetStats();
	{
		SYC_PROFILE_SCOPE("Renderer Prep");

		//syc::RenderCommand::SetClearColor(0.2f, 0.6f, 0.1f, 1);
		syc::RenderCommand::SetClearColor(0.0f, 0.0f, 0.0f, 1);
		syc::RenderCommand::Clear();
	}


	syc::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	m_Level.Draw(m_CameraController.GetCamera().GetPosition(), { bounds.GetWidth(), bounds.GetHeight()});
	/*syc::Renderer2D::DrawQuad({ 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
	syc::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);*/
	syc::Renderer2D::EndScene();
}

void Game::OnImGuiRender()
{
	SYC_PROFILE_SCOPE("ImGuiRenderer Prep");
	syc::OrthographicCameraBounds bounds = m_CameraController.GetBounds();
	m_Level.DrawImGuiLayer(m_CameraController.GetCamera().GetPosition(), { bounds.GetWidth(), bounds.GetHeight() }, m_ImGUIAssets);
}

void Game::OnEvent(syc::Event& event)
{
#ifdef _DEBUG
	m_CameraController.OnEvent(event);
#endif // _DEBUG

}

void* Game::GetUserPtr()
{
	return nullptr;
}
