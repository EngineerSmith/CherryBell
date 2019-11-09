#pragma once
#include "core/input/Input.h"

namespace CherryBell {
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(KeyCode keycode) override;
		bool IsKeyPressedNotRepeatImpl(KeyCode keycode) override;

		bool IsMouseButtonPressedImpl(MouseCode button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}
