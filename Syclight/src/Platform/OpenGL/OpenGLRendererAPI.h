#pragma once

#include "Syclight/Renderer/RendererAPI.h"

namespace syc
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void_ SetClearColor(const glm::vec4& color) override;
		virtual void_ Clear() override;

		virtual void_ DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}



