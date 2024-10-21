#include "sycpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace syc
{
	Ref<Texture2D> Texture2D::Create(uint32 width, uint32 height, uint32 type)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLTexture2D>(width, height, type);
		}
		SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> syc::Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLTexture2D>(path);
		}
		SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

