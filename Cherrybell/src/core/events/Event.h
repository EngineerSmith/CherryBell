#pragma once

#include "core/Core.h"

namespace CherryBell {
	// Events are blocking calls - have to be dealt with as they happen in a frame
	// In the future moving to a queue/buffer for events would stop this blocking call

	enum class EventType {
		Null = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		Null = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class CB_API Event {
		friend class EventDispatcher;
	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) 
		{
			return GetCategoryFlags() & category;
		}

		bool Handled() const { return _handled; }
	protected:
		bool _handled = false;
	};

	class EventDispatcher {
	private:
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: _event(event)
		{}

		template<typename T> //Event
		bool Dispatch(EventFn<T> func)
		{
			if (_event.GetEventType() == T::GetStaticType()) 
			{
				_event._handled = func(*(T*)&_event);
				return true;
			}
			return false;
		}
	private:
		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}