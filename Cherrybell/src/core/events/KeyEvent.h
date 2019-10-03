#pragma once
#include "Event.h"

namespace CherryBell {
	class CB_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return _keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) 
			: _keyCode(keyCode)
		{}

		int _keyCode;
	};

	class CB_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount) 
			: KeyEvent(keyCode), _repeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return _repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _keyCode << " (" << _repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int _repeatCount;
	};

	class CB_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode) 
			: KeyEvent(keyCode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class CB_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << _keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}