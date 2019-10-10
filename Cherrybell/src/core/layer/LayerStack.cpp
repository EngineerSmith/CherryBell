#include "cbpch.h"
#include "LayerStack.h"

namespace CherryBell {
	LayerStack::~LayerStack()
	{
		for (Layer* layer : _layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
		_layerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		_layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);
		if (it != _layers.begin() + _layerInsertIndex)
		{
			layer->OnDetach();
			_layers.erase(it);
			_layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), layer);
		if (it != _layers.end())
		{
			layer->OnDetach();
			_layers.erase(it);
		}
	}
}