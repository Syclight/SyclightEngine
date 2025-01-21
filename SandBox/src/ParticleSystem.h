#pragma once

#include <Syclight.h>

#include "Syclight/Core/Timestep.h"

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	syc::float32 SizeBegin, SizeEnd, SizeVariation;
	syc::float32 LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(syc::uint32 maxParticles);
	ParticleSystem();

	void OnUpdate(syc::Timestep ts);
	void OnRender(syc::OrthographicCamera& camera);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;

	syc::uint32 m_QuadVA = 0;
	syc::Scope<syc::Shader> m_ParticleShader;
	syc::int32 m_ParticleShaderViewProj, m_ParticleShaderTransform, m_ParticleShaderColor;
};
