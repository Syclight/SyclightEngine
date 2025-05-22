#include "sycpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace syc
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		default:
			SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(float32* vertices, size size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		default:
			SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	Ref<IndexBuffer>IndexBuffer::Create(uint32* indices, size count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		default:
			SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}