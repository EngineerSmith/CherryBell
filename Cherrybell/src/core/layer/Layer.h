#pragma once
#include "core/Core.h"
#include "core/events/Event.h"
#include "core/TimeStep.h"

namespace CherryBell {
	class Layer
	{
	public:
		Layer(const char* name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {};
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const char* GetName() const { return _name; }
	protected:
		const char* _name;
	};
}