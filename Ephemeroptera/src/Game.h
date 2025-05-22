#pragma once

#include <Syclight.h>

#include "Level.h"
#include "Actor.h"

#include "Datatype.hpp"
#include "AudioEngine.h"

class Game : public syc::Layer
{
public:
	Game();
	virtual ~Game() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(syc::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(syc::Event& event) override;

	void* GetUserPtr();

private:
	syc::Ref<syc::Shader> m_FlatColorShader;
	syc::OrthographicCameraController m_CameraController;

	syc::float64 m_FrameDeltaTime = 0.0;
	syc::int32 m_FrameCount = 0.0;
	syc::float64 m_FPSTimeCounter = 0.0;
	syc::float64 m_FPS = 0.0;
	/*ParticleSystem m_ParticleSystem{ 100000 };
	ParticleProps m_Particle;*/

	/*syc::Ref<syc::Texture2D> m_SpriteSheet = nullptr;
	syc::Ref<syc::SubTexture2D> m_TextureStairs = nullptr;*/

	Level m_Level;
	ImGUIAssets m_ImGUIAssets;
	AudioEngine m_Audio;
};

