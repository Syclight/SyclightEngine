#pragma once

#include "Syclight/Renderer/OrthographicCamera.h"
#include "Syclight/Core/Timestep.h"

#include "Syclight/Events/ApplicationEvent.h"
#include "Syclight/Events/MouseEvent.h"

namespace syc 
{
	class SYC_API OrthographicCameraController
	{
	public:
		OrthographicCameraController(float32 aspectRatio, bool8 rotation = false);
		OrthographicCameraController(float32 width, float32 height, bool8 rotation = false);

		void_ OnUpdate(Timestep timestep);
		void_ OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool8 OnMouseScrolled(MouseScrolledEvent& e);
		bool8 OnWindowResized(WindowResizeEvent& e);

	private:
		float32 m_AspectRatio;
		float32 m_ZoomLevel = 1.0f;
		float32 m_ZoomSpeed = 0.5f;
		OrthographicCamera m_Camera;

		bool8 m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float32 m_CameraRotation = 0.0f;
		float32 m_CamerTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}
