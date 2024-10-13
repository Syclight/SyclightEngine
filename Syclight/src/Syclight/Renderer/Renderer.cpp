#include "sycpch.h"
#include "Renderer.h"

namespace syc
{
	void_ Renderer::BeginScene()
	{
		return void_();
	}

	void_ Renderer::EndScene()
	{
		return void_();
	}

	void_ Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}