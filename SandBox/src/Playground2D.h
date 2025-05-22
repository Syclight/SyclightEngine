#pragma once

#include "Syclight.h"
#include "Syclight/Core/Timestep.h"
#include "Syclight/Events/Event.h"
#include "ParticleSystem.h"

class Playground2D : public syc::Layer
{
public:
	Playground2D();
	virtual ~Playground2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(syc::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(syc::Event& event) override;

private:
	syc::Ref<syc::Shader> m_FlatColorShader;
	syc::OrthographicCameraController m_CameraController;

	syc::Ref<syc::Texture2D> m_Texture, m_Text0;
	syc::Ref<syc::Texture2D> m_SpriteSheet;
	syc::Ref<syc::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	syc::float64 m_FrameDeltaTime = 0.0;
	syc::int32 m_FrameCount = 0.0;
	syc::float64 m_FPSTimeCounter = 0.0;
	syc::float64 m_FPS = 0.0;

	ParticleSystem m_ParticleSystem{ 100000 };
	ParticleProps m_Particle;
};

