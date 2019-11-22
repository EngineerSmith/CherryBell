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
		CB_PROFILE_FUNCTION();
		CB_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		_window = Window::Create();
		_window->SetEventCallback(CB_BIND_EVENT_FN(Application::OnEvent));
	
		Renderer::Init();

		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);
	}

	Application::~Application()
	{
		Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(CB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(CB_BIND_EVENT_FN(Application::OnWindowResize));

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
			CB_PROFILE_SCOPE("Frame");
			double current = _window->GetTimeSeconds();
			double delta = current - _lastFrameTime;
			_lastFrameTime = current;

			_window->OnUpdate();

			if (!_minimize)
			{
				{
					CB_PROFILE_SCOPE("Update Frame");
					_latency += delta;
					while (_latency >= MS_PER_UPDATE) {
						for (Layer* layer : _layerStack)
							layer->OnUpdate();
						_latency -= MS_PER_UPDATE;
					}
				}

				{
					CB_PROFILE_SCOPE("Render Frame");
					for (Layer* layer : _layerStack)
						layer->OnRender();
				}
			}

			{
				CB_PROFILE_SCOPE("Render ImGUI");
				_imGuiLayer->Begin();
				for (Layer* layer : _layerStack)
					layer->OnImGuiRender();
				_imGuiLayer->End();
			}
		}
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

	bool Application::OnWindowClose(WindowClosedEvent& event)
	{
		_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizedEvent& event)
	{
		_minimize = event.GetWidth() == 0u || event.GetHeight() == 0u;
		if (!_minimize)
			Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}
