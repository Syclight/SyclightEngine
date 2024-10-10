#include "sycpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace syc
{
	VertexBuffer* VertexBuffer::Create(float32* vertices, size1d size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32* indices, size1d count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		default:
			SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}