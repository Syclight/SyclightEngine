#pragma once

#include "Syclight/Renderer/RendererAPI.h"

namespace syc
{
	class SYC_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void_ Init() override;
		virtual void_ SetViewport(int32 x, int32 y, int32 width, int32 height) override;
		virtual void_ SetClearColor(const glm::vec4& color) override;
		virtual void_ Clear() override;
		virtual void_ SetupDepthMask() override;
		virtual void_ ShutdownDepthMask() override;
		virtual void_ SetupDepthTest() override;
		virtual void_ ShutdownDepthTest() override;

		virtual void_ DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}



