#pragma once
#include "core/Core.h"
#include "core/renderer/Window.h"
#include "core/layer/LayerStack.h"
#include "core/events/Event.h"
#include "core/events/ApplicationEvent.h"
#include "core/ImGui/ImGuiLayer.h"
#include "core/TimeStep.h"

namespace CherryBell {
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void Shutdown();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		inline Window& GetWindow() const { return *_window; }
		inline static Application& Get() { return *s_instance; }
	private:
		bool OnWindowClose(WindowClosedEvent& event);
		bool OnWindowResize(WindowResizedEvent& event);
	private:
		Scope<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		bool _minimize = false;
		LayerStack _layerStack;
		double _lastFrameTime = 0.0;
		double _latency = 0.0;
	private:
		static Application* s_instance;
	};

	//To be define in client application - EntryPoint.h
	Application* CreateApplication();
}
