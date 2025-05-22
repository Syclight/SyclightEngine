#include "sycpch.h"
#include "UniformBuffer.h"

#include "Syclight/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace syc
{
	Ref<UniformBuffer> syc::UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

