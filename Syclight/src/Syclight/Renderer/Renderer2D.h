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
		static void_ Flush();

		// Primitives
		static void_ DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void_ DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void_ DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float32 tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void_ DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float32 tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		static void_ DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, const float32 rotate, const glm::vec4& color);
		static void_ DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, const float32 rotate, const glm::vec4& color);
		static void_ DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, const float32 rotate, const Ref<Texture2D>& texture, const float32 tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void_ DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, const float32 rotate, const Ref<Texture2D>& texture, const float32 tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));


	};
}

