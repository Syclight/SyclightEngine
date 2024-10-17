#include "sycpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace syc
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void_ Renderer::Init()
	{
		RenderCommand::Init();
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
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniforMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniforMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}