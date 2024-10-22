#include "sycpch.h"
#include "WindowsWindow.h"

#include "Syclight/Events/ApplicationEvent.h"
#include "Syclight/Events/KeyEvent.h"
#include "Syclight/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace syc
{
	static uint8 s_GLFWWindowCount = 0;

	static void_ GLFWErrorCallback(int32 error, const char8* description)
	{
		SYC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	SycWindow* SycWindow::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		SYC_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void_ WindowsWindow::Init(const WindowProps& props)
	{
		SYC_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SYC_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (s_GLFWWindowCount == 0)
		{
			int32 success = glfwInit();
			/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
			SYC_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_Window = glfwCreateWindow((int32)m_Data.Width, (int32)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW 回调函数
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32 width, int32 height) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
					default:
						break;
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32 keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32 button, int32 action, int32 mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, float64 xOffset, float64 yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float32)xOffset, (float32)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, float64 xPos, float64 yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float32)xPos, (float32)yPos);
				data.EventCallback(event);
			});
	}

	void_ WindowsWindow::Shutdown()
	{
		SYC_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void_ WindowsWindow::OnUpdate()
	{
		SYC_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void_ WindowsWindow::SetVSync(bool8 enabled)
	{
		SYC_PROFILE_FUNCTION();

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

	bool8 WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}

