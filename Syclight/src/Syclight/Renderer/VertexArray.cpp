#include "sycpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace syc
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:      SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:    return new OpenGLVertexArray();
		}
		SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}