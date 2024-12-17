#pragma once

#include "Syclight/Events/Event.h"

namespace syc
{
	struct WindowProps
	{
		std::string Title;
		uint32 Width;
		uint32 Height;

		WindowProps(
			const std::string& title = "Syclight Engine Window",
			uint32 width = WIND_WIDTH,
			uint32 height = WIND_HEIGHT)
			: Title(title), Width(width), Height(height)
		{}
	};

	class SYC_API SycWindow
	{
	public:
		using EventCallbackFn = std::function<void_(Event&)>;

		virtual ~SycWindow() {}

		virtual void OnUpdate() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual std::pair<uint32, uint32> GetCenter() const = 0;

		//窗口属性
		virtual void_ SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void_ SetVSync(bool enabled) = 0;
		virtual bool8 IsVSync() const = 0;
		virtual void_ SetWindowSize(uint32 width, uint32 height) = 0;

		virtual void_* GetNativeWindow() const = 0;

		static SycWindow* Create(const WindowProps& props = WindowProps());
	};
}