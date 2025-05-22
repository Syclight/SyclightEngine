#pragma once

#include "Syclight/Renderer/OrthographicCamera.h"
#include "Syclight/Core/Timestep.h"

#include "Syclight/Events/ApplicationEvent.h"
#include "Syclight/Events/MouseEvent.h"

namespace syc 
{
	struct OrthographicCameraBounds
	{
		float32 Left, Right;
		float32 Bottom, Top;
		float32 GetWidth() const { return Right - Left; }
		float32 GetHeight() const { return Top - Bottom; }
	};

	class SYC_API OrthographicCameraController
	{
	public:
		OrthographicCameraController(float32 aspectRatio, bool8 rotation = false);
		OrthographicCameraController(float32 width, float32 height, bool8 rotation = false);

		void_ OnUpdate(Timestep timestep);
		void_ OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void_ SetZoomLevel(float32 level) { m_ZoomLevel = level;  CalculateView(); }
		float32 GetZoomLevel() const { return m_ZoomLevel; }

		void_ SetCameraPos(const glm::vec3& pos) { m_CameraPosition = pos;  m_Camera.SetPosition(m_CameraPosition); }
		void_ SetCameraPos(float32 x, float32 y, float32 z) { m_CameraPosition = {x, y, z};  m_Camera.SetPosition(m_CameraPosition); }
		const glm::vec3 GetCameraPos() const { return m_CameraPosition; }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

	private:
		void_ CalculateView();

		bool8 OnMouseScrolled(MouseScrolledEvent& e);
		bool8 OnWindowResized(WindowResizeEvent& e);

	private:
		float32 m_AspectRatio;
		float32 m_ZoomLevel = 1.0f;
		float32 m_ZoomSpeed = 0.5f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		bool8 m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float32 m_CameraRotation = 0.0f;
		float32 m_CamerTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}
