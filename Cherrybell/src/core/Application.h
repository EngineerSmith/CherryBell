#pragma once
#include "core/Core.h"
#include "core/Window.h"
#include "core/LayerStack.h"
#include "core/events/Event.h"
#include "core/events/ApplicationEvent.h"

#include "core/ImGui/ImGuiLayer.h"

#include "core/renderer/Shader.h"
#include "core/renderer/Buffer.h"
#include "core/renderer/VertexArray.h"

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
		std::unique_ptr<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		LayerStack _layerStack;
		
		std::shared_ptr<Shader> _shader;
		std::shared_ptr<VertexArray> _vertexArray;

		static Application* s_instance;
	};

	//To be define in client application - EntryPoint.h
	Application* CreateApplication();
}
