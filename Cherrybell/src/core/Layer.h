#pragma once
#include "core/Core.h"
#include "core/events/Event.h"

#include <string>

namespace CherryBell {
	class CB_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		// Debug - shouldn't be relyed on
		inline const std::string& GetName() const { return _name; }
	protected:
		std::string _name; // Debug
	};
}