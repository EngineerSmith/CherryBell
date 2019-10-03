#pragma once
#include "core/Core.h"
#include "core/Window.h"
#include "core/LayerStack.h"
#include "core/events/Event.h"
#include "core/events/ApplicationEvent.h"


namespace CherryBell {
	class CB_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> _window;
		bool _running = true;
		LayerStack _layerStack;
	};

	//To be define in client application - EntryPoint.h
	Application* CreateApplication();
}
