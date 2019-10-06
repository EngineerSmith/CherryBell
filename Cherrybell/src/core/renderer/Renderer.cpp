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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4(_sceneData.ViewProjectionMatrix, "u_viewProjection");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}