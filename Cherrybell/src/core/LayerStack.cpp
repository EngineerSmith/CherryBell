#include "cbpch.h"
#include "LayerStack.h"

namespace CherryBell {
	LayerStack::LayerStack()
	{
		_layerInsert = _layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : _layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		_layerInsert = _layers.emplace(_layerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		_layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(_layers.begin(), _layers.end(), layer);
		if (it != _layers.end())
		{
			_layers.erase(it);
			_layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(_layers.begin(), _layers.end(), layer);
		if (it != _layers.end())
			_layers.erase(it);
	}
}