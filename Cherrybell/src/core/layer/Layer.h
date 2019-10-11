#pragma once
#include "core/Core.h"
#include "core/events/Event.h"
#include "core/TimeStep.h"

#include <string>

namespace CherryBell {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {};
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		// For debugging - shouldn't be relyed on
		inline const std::string& GetName() const { return _name; }
	protected:
		std::string _name; // Debug
	};
}