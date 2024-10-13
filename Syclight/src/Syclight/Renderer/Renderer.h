#pragma once

#include "RenderCommand.h"

namespace syc
{
	class SYC_API Renderer
	{
	public:
		static void_ BeginScene();
		static void_ EndScene();

		static void_ Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}


