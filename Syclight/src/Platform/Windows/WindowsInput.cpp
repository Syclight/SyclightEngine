#include "sycpch.h"
#include "WindowsInput.h"

#include "Syclight/Application.h"
#include <GLFW/glfw3.h>

namespace syc
{
	Input* Input::s_Instance = new WindowsInput();

	bool4 WindowsInput::IsKeyPressedImpl(int16 keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool4 WindowsInput::IsMouseButtonImpl(int16 button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	Pos2d WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		float32 xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float16)xpos, (float16)ypos };
	}

	float16 WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float16 WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}