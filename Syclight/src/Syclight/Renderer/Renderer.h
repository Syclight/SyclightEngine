#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace syc
{
	class SYC_API Renderer
	{
	public:
		static void_ Init();
		static void_ OnWindowResize(uint32 width, uint32 height);

		static void_ BeginScene(OrthographicCamera& camera);
		static void_ EndScene();

		static void_ Submit(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}


