#include "ParticleSystem.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem(syc::uint32 maxParticles):
	m_PoolIndex(maxParticles - 1)
{
	m_ParticlePool.resize(maxParticles);
	/*m_ParticleShader = syc::Shader::Create("assets/shaders/Particle.glsl");
	m_ParticleShaderViewProj = m_ParticleShader->GetUniformLocation("u_ViewProjection");
	m_ParticleShaderTransform = m_ParticleShader->GetUniformLocation("u_Transform");
	m_ParticleShaderColor = m_ParticleShader->GetUniformLocation("u_Color");
	float quadVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	uint32_t quadIndices[] = {
		0, 1, 2,
		2, 3, 0
	};
	m_QuadVA = syc::VertexArray::Create();
	syc::Ref<syc::VertexBuffer> quadVB = syc::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	quadVB->SetLayout({
		{syc::ShaderDataType::Float3, "a_Position"}
		});
	m_QuadVA->AddVertexBuffer(quadVB);
	syc::Ref<syc::IndexBuffer> quadIB = syc::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
	m_QuadVA->SetIndexBuffer(quadIB);*/
}

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::OnUpdate(syc::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender(syc::OrthographicCamera& camera)
{
	syc::Renderer2D::BeginScene(camera);
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		color.a = color.a * life;
		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		glm::vec3 position{ particle.Position.x, particle.Position.y, 0.2f };
		syc::Renderer2D::DrawRotateQuad(position, { size, size }, glm::radians(particle.Rotation), color);
	}
	syc::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = syc::Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (syc::Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (syc::Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (syc::Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
