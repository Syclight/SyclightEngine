#pragma once

#include "Syclight/Window.h"
#include "Syclight/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace syc
{
	class WindowsWindow : public SycWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void_ OnUpdate() override;

		inline uint16 GetWidth() const override { return m_Data.Width; }
		inline uint16 GetHeight() const override { return m_Data.Height; }

		//窗口属性
		inline void_ SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void_ SetVSync(bool4 enabled) override;
		bool4 IsVSync() const override;
		void_* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void_ Init(const WindowProps& props);
		virtual void_ Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			uint16 Width, Height;
			bool4 VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}


