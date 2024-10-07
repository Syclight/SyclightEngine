#pragma once

#include "Syclight/Common.h"
#include "Syclight/Core.h"
#include "Syclight/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace syc
{
	class SYC_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void_ Init() override;
		virtual void_ SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}


