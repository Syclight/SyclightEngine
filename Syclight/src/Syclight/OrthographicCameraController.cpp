#include "sycpch.h"
#include "OrthographicCameraController.h"

#include "Syclight/Input.h"
#include "Syclight/KeyCodes.h"

namespace syc 
{
	OrthographicCameraController::OrthographicCameraController(float32 aspectRatio, bool8 rotation)
		:m_AspectRatio(aspectRatio),
		m_Rotation(rotation),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	OrthographicCameraController::OrthographicCameraController(float32 width, float32 height, bool8 rotation)
		:m_AspectRatio(width / height),
		m_Rotation(rotation),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void_ OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		if (Input::IsKeyPressed(SYC_KEY_A))
		{
			m_CameraPosition.x -= m_CamerTranslationSpeed * timestep;
		}
		else if (Input::IsKeyPressed(SYC_KEY_D))
		{
			m_CameraPosition.x += m_CamerTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(SYC_KEY_W))
		{
			m_CameraPosition.y += m_CamerTranslationSpeed * timestep;
		}
		else if (Input::IsKeyPressed(SYC_KEY_S))
		{
			m_CameraPosition.y -= m_CamerTranslationSpeed * timestep;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(SYC_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * timestep;
			}
			if (Input::IsKeyPressed(SYC_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * timestep;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CamerTranslationSpeed = m_ZoomLevel;
	}

	void_ OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SYC_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SYC_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool8 OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * m_ZoomSpeed;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool8 OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float32)e.GetWidth() / (float32)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}