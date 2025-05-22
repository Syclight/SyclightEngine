#pragma once

#include "Syclight/Renderer/OrthographicCamera.h"
#include "Syclight/Renderer/Texture.h"
#include "Syclight/Renderer/SubTexture2D.h"

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
		static void_ DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const float32 tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void_ DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const float32 tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		static void_ DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, const float32 rotate, const glm::vec4& color);
		static void_ DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, const float32 rotate, const glm::vec4& color);
		static void_ DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, const float32 rotate, const Ref<Texture2D>& texture, const float32 tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void_ DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, const float32 rotate, const Ref<Texture2D>& texture, const float32 tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void_ DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, const float32 rotate, const Ref<SubTexture2D>& subTexture, const float32 tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));
		static void_ DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, const float32 rotate, const Ref<SubTexture2D>& subTexture, const float32 tilingFactor = 1.0f, glm::vec4 tintColor = glm::vec4(1.0f));

		static void_ DrawCircle(const glm::mat4& transform, const glm::vec4& color, float32 thickness = 1.0f, float32 fade = 0.005f, int32 entityID = -1);
		static void_ DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color, int32 entityID = -1);
		static void_ DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int32 entityID = -1);
		static void_ DrawRect(const glm::mat4& transform, const glm::vec4& color, int32 entityID = -1);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void_ ResetStats();
		static Statistics GetStats();

	private:
		static void_ TestFlushAndNewBatch();
		static void_ StartBatch();
		static void_ NextBatch();
	};
}

