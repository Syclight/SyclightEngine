#pragma once

#include "Event.h"

#include <sstream>

namespace syc
{
	class SYC_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint16 width, uint16 height)
			: m_Width(width), m_Height(height) {}
		inline uint16 GetWidth() const { return m_Width; }
		inline uint16 GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		uint16 m_Width, m_Height;
	};

	class SYC_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class SYC_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class SYC_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {};

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class SYC_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {};

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}