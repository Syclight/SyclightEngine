#include "sycpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace syc
{
	Ref<Texture2D> syc::Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SYC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLTexture2D>(path);
		}
		SYC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

