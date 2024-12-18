#include "sycpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace syc
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void_ Renderer::Init()
	{
		SYC_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void_ Renderer::OnWindowResize(uint32 width, uint32 height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void_ Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void_ Renderer::EndScene()
	{
		return void_();
	}

	void_ Renderer::Submit(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}