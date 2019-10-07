#pragma once
#include "core/Core.h"
#include "core/Window.h"
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

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() const { return *_window; }
		inline static Application& Get() { return *s_instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		//TODO allow for more than one window per application
		Scope<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		LayerStack _layerStack;
		float _lastFrameTime = 0.0f;
	private:
		static Application* s_instance;
	};

	//To be define in client application - EntryPoint.h
	Application* CreateApplication();
}
