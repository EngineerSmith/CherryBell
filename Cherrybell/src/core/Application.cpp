#include "cbpch.h"
#include "Application.h"
#include "core/events/Event.h"
#include "core/Log.h"
#include "core/renderer/Renderer.h"
#include "core/input/Input.h"

namespace CherryBell {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		CB_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		_window = Scope<Window>(Window::Create());
		_window->SetEventCallback(CB_BIND_EVENT_FN(Application::OnEvent));
	
		Renderer::Init();

		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		} 
	}

	void Application::Run()
	{
		_lastFrameTime = _window->GetTimeSeconds();
		while (_running)
		{
			double current = _window->GetTimeSeconds();
			double delta = current - _lastFrameTime;
			_lastFrameTime = current;

			_window->OnUpdate();

			if (!_minimize)
			{
				_latency += delta;
				while (_latency >= MS_PER_UPDATE) {
					for (Layer* layer : _layerStack)
						layer->OnUpdate();
					_latency -= MS_PER_UPDATE;
				}

				for (Layer* layer : _layerStack)
					layer->OnRender();
			}

			_imGuiLayer->Begin();
			for (Layer* layer : _layerStack)
				layer->OnImGuiRender();
			_imGuiLayer->End();
		}
		Shutdown();
	}

	void Application::Shutdown()
	{
		CB_CORE_INFO("Shutting down application");
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		_layerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		_layerStack.PopOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		_minimize = event.GetWidth() == 0u || event.GetHeight() == 0u;
		if (!_minimize)
			Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}