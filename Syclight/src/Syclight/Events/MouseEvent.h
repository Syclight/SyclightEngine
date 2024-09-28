#pragma once

#include "Event.h"

namespace syc
{
	class SYC_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float16 x, float16 y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float16 GetX() const { return m_MouseX; }
		inline float16 GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float16 m_MouseX, m_MouseY;
	};

	class SYC_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float16 xOffset, float16 yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float16 GetXOffset() const { return m_XOffset; }
		inline float16 GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float16 m_XOffset, m_YOffset;
	};

	class SYC_API MouseButtonEvent : public Event
	{
	public:
		inline int16 GetButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int16 button)
			: m_Button(button) {}
		int16 m_Button;
	};

	class SYC_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int16 button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class SYC_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int16 button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}