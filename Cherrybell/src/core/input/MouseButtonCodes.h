#pragma once

namespace CherryBell {
	enum class MouseCode
	{
		// Codes from glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,
		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define CB_MOUSE_BUTTON_1         ::CherryBell::MouseCode::Button0
#define CB_MOUSE_BUTTON_2         ::CherryBell::MouseCode::Button1
#define CB_MOUSE_BUTTON_3         ::CherryBell::MouseCode::Button2
#define CB_MOUSE_BUTTON_4         ::CherryBell::MouseCode::Button3
#define CB_MOUSE_BUTTON_5         ::CherryBell::MouseCode::Button4
#define CB_MOUSE_BUTTON_6         ::CherryBell::MouseCode::Button5
#define CB_MOUSE_BUTTON_7         ::CherryBell::MouseCode::Button6
#define CB_MOUSE_BUTTON_8         ::CherryBell::MouseCode::Button7
#define CB_MOUSE_BUTTON_LAST      ::CherryBell::MouseCode::ButtonLast
#define CB_MOUSE_BUTTON_LEFT      ::CherryBell::MouseCode::ButtonLeft
#define CB_MOUSE_BUTTON_RIGHT     ::CherryBell::MouseCode::ButtonRight
#define CB_MOUSE_BUTTON_MIDDLE    ::CherryBell::MouseCode::ButtonMiddle
