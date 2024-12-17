#pragma once

#include "RendererAPI.h"

namespace syc
{
	class SYC_API RenderCommand
	{
	public:
		inline static void_ Init()
		{
			s_RendererAPI->Init();
		}

		inline static void_ SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void_ SetClearColor(float32 r, float32 g, float32 b, float32 a=1.0f)
		{
			s_RendererAPI->SetClearColor({ r, g, b, a });
		}

		inline static void_ Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void_ SetupDepthMask()
		{
			s_RendererAPI->SetupDepthMask();
		}

		inline static void_ ShutdownDepthMask()
		{
			s_RendererAPI->ShutdownDepthMask();
		}

		inline static void_ DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void_ SetupDepthTest()
		{
			s_RendererAPI->SetupDepthTest();
		}

		inline static void_ ShutdownDepthTest()
		{
			s_RendererAPI->ShutdownDepthTest();
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}