#include "sycpch.h"
#include "WindowsInput.h"

#include "Syclight/Application.h"
#include <GLFW/glfw3.h>

namespace syc
{
	Input* Input::s_Instance = new WindowsInput();

	bool8 WindowsInput::IsKeyPressedImpl(int32 keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool8 WindowsInput::IsMouseButtonImpl(int32 button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	Pos2d WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		float64 xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float32)xpos, (float32)ypos };
	}

	float32 WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float32 WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}