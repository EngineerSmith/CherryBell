#pragma once
#include "core/events/Event.h"

#include <sstream>

namespace CherryBell {
	class  WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: _width(width), _height(height)
		{}

		inline unsigned int GetWidth() const { return _width; }
		inline unsigned int GetHeight() const { return _height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << _width << ", " << _height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int _width, _height;
	};

	class WindowFocusedEvent : public Event
	{
	public:
		WindowFocusedEvent() = default;

		EVENT_CLASS_TYPE(WindowFocused)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int x, int y)
			: _x(x), _y(y) {}

		inline int GetX() const { return _x; }
		inline int GetY() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent: " << _x << ", " << _y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		int _x, _y;
	};
}
