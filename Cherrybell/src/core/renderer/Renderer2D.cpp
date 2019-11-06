#include "cbpch.h"
#include "Renderer2D.h"
#include "core/renderer/RenderCommand.h"
#include "core/renderer/Shader.h"
#include "core/renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

//TEMP
#include "platform/OpenGL/OpenGLShader.h"

namespace CherryBell
{
	struct Renderer2DData
	{
		ShaderLibrary ShaderLibrary;
		Ref<VertexArray> VertexArray;
	};

	static Renderer2DData* s_Data = nullptr;

	void Renderer2D::Init()
	{ 
		s_Data = new Renderer2DData();

		s_Data->VertexArray = VertexArray::Create();

		float vertices[] = {
			//a_position	   
			 -0.5f, -0.5f, 0.0f,
			  0.5f, -0.5f, 0.0f,
			  0.5f,  0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f
		};
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_position"}
		};

		vertexBuffer->SetLayout(layout);
		s_Data->VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0u,1u,2u, 2u,3u,0u };

		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		s_Data->VertexArray->SetIndexBuffer(indexBuffer);

		s_Data->ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
		s_Data = nullptr;
	}

	void Renderer2D::BeginScene(const OrthorgraphicCamera& camera)
	{ 
		auto& shader = s_Data->ShaderLibrary.Get("FlatColor");
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(camera.GetViewProjectionMatrix(), "u_viewProjection");
	}

	void Renderer2D::EndScene()
	{ }

	void Renderer2D::FillQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{ 
		FillQuad(glm::vec3(position, 0), size, color);
	}

	void Renderer2D::FillQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{ 
		auto& shader = s_Data->ShaderLibrary.Get("FlatColor");
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4(color, "u_color");
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1));
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(transform, "u_transform");
	
		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
	}
}