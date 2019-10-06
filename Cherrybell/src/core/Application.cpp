#include "cbpch.h"
#include "Application.h"
#include "core/events/Event.h"
#include "core/Log.h"

#include <glad/glad.h>

#include "core/Input.h"

namespace CherryBell {
	Application* Application::s_instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
		default:
			CB_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	Application::Application()
	{
		CB_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	
		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);


		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f
		};

		_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "_position" },
			{ShaderDataType::Float4, "_color" }
		};
			
		_vertexBuffer->SetLayout(layout);

		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
						element.GetComponentCount(), 
						ShaderDataTypeToOpenGLBaseType(element.Type), 
						element.Normalized ? GL_TRUE : GL_FALSE, 
						layout.GetStride(), 
						(const void*)element.Offset
			);
			index++;
		}

		uint32_t indices[3] = { 0u,1u,2u };
		
		_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

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

		_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);

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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			_shader->Bind();

			glBindVertexArray(_vertexArray);
			glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : _layerStack)
				layer->OnUpdate();

			// TODO move to render thread
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