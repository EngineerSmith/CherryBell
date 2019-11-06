#include "cbpch.h"
#include "Renderer2D.h"
#include "core/renderer/RenderCommand.h"
#include "core/renderer/Shader.h"
#include "core/renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

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
			//a_position	   //a_texCoord
			 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_position"},
			{ShaderDataType::Float2, "a_texCoord"}
		};

		vertexBuffer->SetLayout(layout);
		s_Data->VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0u,1u,2u, 2u,3u,0u };

		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		s_Data->VertexArray->SetIndexBuffer(indexBuffer);

		s_Data->ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
		auto& shader = s_Data->ShaderLibrary.Load("assets/shaders/Texture.glsl");
		shader->Bind();
		shader->Set(0, "u_texture");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
		s_Data = nullptr;
	}

	void Renderer2D::BeginScene(const OrthorgraphicCamera& camera)
	{ 
		for (auto& shader : s_Data->ShaderLibrary)
		{
			shader.second->Bind();
			shader.second->Set(camera.GetViewProjectionMatrix(), "u_viewProjection");
		}
	}

	void Renderer2D::EndScene()
	{ }

	void Renderer2D::FillQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{ 
		FillQuad(glm::vec3(position, 0), size, rotation, color);
	}

	void Renderer2D::FillQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{ 
		DrawQuad(position, size, rotation, color, DrawType::Fill);
	}

	void Renderer2D::LineQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{
		LineQuad(glm::vec3(position, 0), size, rotation, color);
	}

	void Renderer2D::LineQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{
		DrawQuad(position, size, rotation, color, DrawType::Line);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const DrawType drawType)
	{
		auto& shader = s_Data->ShaderLibrary.Get("FlatColor");
		shader->Bind();
		shader->Set(color, "u_color");
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, {0,0,1}) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1));
		shader->Set(transform, "u_transform");

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray, drawType);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const Ref<Texture2D>& texture, const DrawType drawType)
	{
		auto& shader = s_Data->ShaderLibrary.Get("Texture");
		shader->Bind();
		shader->Set(color, "u_color");
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0,0,1 }) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1));
		shader->Set(transform, "u_transform");
		
		texture->Bind();

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray, drawType);
	}
}