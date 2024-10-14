#include "sycpch.h"
#include "Renderer.h"

namespace syc
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void_ Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void_ Renderer::EndScene()
	{
		return void_();
	}

	void_ Renderer::Submit(std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniforMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}