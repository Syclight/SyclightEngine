#pragma once

#include "Syclight/Events/Event.h"

namespace syc
{
	struct WindowProps
	{
		std::string Title;
		uint16 Width;
		uint16 Height;

		WindowProps(
			const std::string& title = "Syclight Engine",
			uint16 width = 1920,
			uint16 height = 1080)
			: Title(title), Width(width), Height(height)
		{}
	};

	class SYC_API SycWindow
	{
	public:
		using EventCallbackFn = std::function<void_(Event&)>;

		virtual ~SycWindow() {}

		virtual void OnUpdate() = 0;

		virtual uint16 GetWidth() const = 0;
		virtual uint16 GetHeight() const = 0;

		//窗口属性
		virtual void_ SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void_ SetVSync(bool enabled) = 0;
		virtual bool4 IsVSync() const = 0;

		virtual void_* GetNativeWindow() const = 0;

		static SycWindow* Create(const WindowProps& props = WindowProps());
	};
}