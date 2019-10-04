#pragma once
#include "core/Core.h"
#include "core/Layer.h"

#include <vector>

namespace CherryBell {
	class LayerStack 
	{
	public:
		LayerStack();
		~LayerStack();
	
		void PushLayer(Layer* layer); // Takes ownership of pointer and deletes it if this object is deleted
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer); // Does not delete layer for you, gives up ownership of layer
		void PopOverlay(Layer* layer);
	
		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
	private:
		std::vector<Layer*> _layers;
		unsigned int _layerInsertIndex = 0;
	};
}