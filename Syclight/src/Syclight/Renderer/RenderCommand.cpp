#include "sycpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace syc
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}