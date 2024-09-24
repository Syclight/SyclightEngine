#include "sycpch.h"
#include "WindowsWindow.h"

#include "Syclight/Log.h"

namespace syc
{
	static bool4 s_GLFWInitialized = false;

	SycWindow* SycWindow::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void_ WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SYC_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			int16 success = glfwInit();
			SYC_CORE_ASSERT(success, "Could not intialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int16)m_Data.Width, (int16)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void_ WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void_ WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void_ WindowsWindow::SetVSync(bool4 enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool4 WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}

