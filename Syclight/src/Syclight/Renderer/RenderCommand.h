#pragma once

#include "RendererAPI.h"

namespace syc
{
	class SYC_API RenderCommand
	{
	public:
		inline static void_ SetClearColor(float32 r, float32 g, float32 b, float32 a=1.0f)
		{
			s_RendererAPI->SetClearColor({ r, g, b, a });
		}

		inline static void_ Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void_ DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}