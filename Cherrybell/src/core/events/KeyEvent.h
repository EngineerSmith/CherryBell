#pragma once
#include "core/events/Event.h"
#include "core/input/KeyCodes.h"

namespace CherryBell {
	class KeyEvent : public Event {
	public:
		inline KeyCode GetKeyCode() const { return _keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode keyCode) 
			: _keyCode(keyCode)
		{}

		KeyCode _keyCode;
	};

	class  KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KeyCode keyCode, int repeatCount) 
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

	class  KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(KeyCode keyCode) 
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

	class  KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(KeyCode keyCode)
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
