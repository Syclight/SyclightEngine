#pragma once

#include "Syclight/Core/Core.h"
#include "sycpch.h"

namespace syc {
	enum class EventType
	{
		Nome = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFoucus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
		virtual EventType GetEventType() const override { return GetStaticType(); }\
		virtual const char8* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int32 GetCategoryFlags() const override { return category; }

	class SYC_API Event
	{
		// friend class EventDispatcher;

	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char8* GetName() const = 0;
		virtual int32 GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	public:
		bool8 Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{
		}

		template<typename T>
		bool8 Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//m_Event.Handled |= func(static_cast<T&>(m_Event));
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		// std::cout << e.ToString() << "\n";
		return os << e.ToString();
	}
}