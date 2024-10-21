#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace syc
{
	class SYC_API Renderer2D
	{
	public:
		static void_ Init();
		static void_ Shutdown();

		static void_ BeginScene(const OrthographicCamera& camera);
		static void_ EndScene();

		// Primitives
		static void_ DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void_ DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void_ DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void_ DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};
}

