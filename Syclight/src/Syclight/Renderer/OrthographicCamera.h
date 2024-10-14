#pragma once

#include "Syclight/Common.h"
#include <glm/glm.hpp>


namespace syc
{
	class SYC_API OrthographicCamera
	{
	public:
		OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top);


		const glm::vec3 GetPosition() const { return m_Position; }
		void_ SetPosition(float32 x, float32 y, float32 z) { SetPosition({ x, y, z }); }
		void_ SetPosition(const glm::vec3& position) 
		{ 
			m_Position = position;
			RecalculateViewMartix();
		}

		float32 GetRotation() const { return m_Rotation; }
		void_ SetRotation(float32 rotation)
		{ 
			m_Rotation = rotation;
			RecalculateViewMartix();
		}

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void_ RecalculateViewMartix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f};
		float32 m_Rotation = 0.0f;
	};
}
