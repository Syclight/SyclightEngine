#include "sycpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace syc
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SYC_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void_ OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SYC_CORE_ASSERT(status, "Failed to initailize Glad");

		SYC_CORE_INFO("OpenGL Info:");
		SYC_CORE_INFO("   Vender: {0}", glGetString(GL_VENDOR));
		SYC_CORE_INFO("   Renderer: {0}", glGetString(GL_RENDERER));
		SYC_CORE_INFO("   Version: {0}", glGetString(GL_VERSION));

	#ifdef SYC_ENABLE_ASSERTS
		int32 versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		SYC_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Syclight requires at least OpenGL version 4.5!")
	#endif // SYC_ENABLE_ASSERTS

	}

	void_ OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}