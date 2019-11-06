#include "cbpch.h"
#include "Renderer.h"
#include "core/renderer/Renderer2D.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace CherryBell {
	Scope<Renderer::SceneData> Renderer::_sceneData = CreateScope<Renderer::SceneData>(glm::mat4(1.0f));

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthorgraphicCamera& camera)
	{ 
		_sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{ }

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(_sceneData->ViewProjectionMatrix, "u_viewProjection");
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(transform, "u_transform");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}