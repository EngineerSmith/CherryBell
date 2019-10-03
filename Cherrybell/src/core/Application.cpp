#include "cbpch.h"
#include "Application.h"
#include "core/events/Event.h"
#include "core/Log.h"

#include <glad/glad.h>

namespace CherryBell {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		CB_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::Run()
	{
		while (_running)
		{
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : _layerStack)
				layer->OnUpdate();

			_window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}