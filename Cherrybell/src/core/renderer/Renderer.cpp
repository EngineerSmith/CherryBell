#include "cbpch.h"
#include "Renderer.h"

namespace CherryBell {
	Renderer::SceneData Renderer::_sceneData = { glm::mat4(1.0f) };

	void Renderer::BeginScene(OrthorgraphicCamera& camera)
	{ 
		_sceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{ }

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4(_sceneData.ViewProjectionMatrix, "u_viewProjection");
		shader->UploadUniformMat4(transform, "u_transform");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}