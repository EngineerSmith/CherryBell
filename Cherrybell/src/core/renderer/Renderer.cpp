#include "cbpch.h"
#include "Renderer.h"

#include "platform/OpenGL/OpenGLShader.h"

namespace CherryBell {
	Renderer::SceneData Renderer::_sceneData = { glm::mat4(1.0f) };

	void Renderer::BeginScene(OrthorgraphicCamera& camera)
	{ 
		_sceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{ }

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(_sceneData.ViewProjectionMatrix, "u_viewProjection");
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(transform, "u_transform");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}