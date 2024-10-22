#pragma once

#include "Syclight.h"
#include "Syclight/Core/Timestep.h"
#include "Syclight/Events/Event.h"

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
	syc::Ref<syc::VertexArray> m_SquareVA;
	syc::Ref<syc::Shader> m_FlatColorShader;
	syc::OrthographicCameraController m_CameraController;
	syc::Ref<syc::Texture2D> m_Texture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

