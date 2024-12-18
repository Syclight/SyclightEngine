#include "sycpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace syc
{
	void_ OpenGLRendererAPI::Init()
	{
		SYC_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void_ OpenGLRendererAPI::SetViewport(int32 x, int32 y, int32 width, int32 height)
	{
		glViewport(x, y, width, height);
	}

	void_ OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void_ OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void_ OpenGLRendererAPI::SetupDepthMask()
	{
		glDepthMask(GL_TRUE);
	}

	void_ OpenGLRendererAPI::ShutdownDepthMask()
	{
		glDepthMask(GL_FALSE);
	}

	void_ OpenGLRendererAPI::SetupDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void_ OpenGLRendererAPI::ShutdownDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void_ OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
