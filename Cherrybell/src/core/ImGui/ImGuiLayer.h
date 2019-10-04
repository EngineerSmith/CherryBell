#pragma once
#include "core/Layer.h"
#include "core/events/MouseEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/ApplicationEvent.h"

namespace CherryBell {
	class CB_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float _time = 0.0f;
	};
}