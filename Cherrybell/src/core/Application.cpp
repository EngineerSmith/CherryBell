#include "cbpch.h"
#include "Application.h"
#include "core/events/Event.h"
#include "core/Log.h"
#include "core/renderer/Renderer.h"

#include "core/Input.h"

namespace CherryBell {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		CB_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	
		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);

		_vertexArray.reset(VertexArray::Create());
		
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "_position"},
			{ShaderDataType::Float4, "_color"}
		};
			
		vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0u,1u,2u };
		
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		_vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _position;
			layout(location = 1) in vec4 _color;

			out vec3 position;
			out vec4 color;

			void main()
			{
				position = _position;
				color = _color;
				gl_Position = vec4(_position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 _color;
			
			in vec3 position;
			in vec4 color;

			void main()
			{
				_color = color;
			}
		)";

		_shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);

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
			RenderCommand::SetClearColor({1.0, 0.0, 1.0, 1.0});
			RenderCommand::Clear();

			Renderer::BeginScene();

			_shader->Bind();
			Renderer::Submit(_vertexArray);

			Renderer::EndScene();

			for (Layer* layer : _layerStack)
				layer->OnUpdate();

			_imGuiLayer->Begin();
			for (Layer* layer : _layerStack)
				layer->OnImGuiRender();
			_imGuiLayer->End();

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