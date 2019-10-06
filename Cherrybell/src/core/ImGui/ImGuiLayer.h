#pragma once
#include "core/layer/Layer.h"
#include "core/events/MouseEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/ApplicationEvent.h"

namespace CherryBell {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};
}