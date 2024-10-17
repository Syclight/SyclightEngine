#pragma once

#include "Syclight/Renderer/RendererAPI.h"

namespace syc
{
	class SYC_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void_ Init() override;
		virtual void_ SetClearColor(const glm::vec4& color) override;
		virtual void_ Clear() override;

		virtual void_ DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}



