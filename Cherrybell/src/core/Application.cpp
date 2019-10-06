#include "cbpch.h"
#include "Application.h"
#include "core/events/Event.h"
#include "core/Log.h"
#include "core/renderer/Renderer.h"

#include "core/Input.h"

namespace CherryBell {
	Application* Application::s_instance = nullptr;

	Application::Application()
		: _camera(-1.6f, 1.6f, -0.9f, 0.9f)
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
			{ShaderDataType::Float3, "a_position"},
			{ShaderDataType::Float4, "a_color"}
		};
			
		vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0u,1u,2u };
		
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		_vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			uniform mat4 u_viewProjection;

			out vec3 v_position;
			out vec4 v_color;

			void main()
			{
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_viewProjection * vec4(a_position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 _color;
			
			in vec3 v_position;
			in vec4 v_color;

			void main()
			{
				_color = v_color;
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

			Renderer::BeginScene(_camera);

			Renderer::Submit(_shader, _vertexArray);

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