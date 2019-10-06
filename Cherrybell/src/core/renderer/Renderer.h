#pragma once
#include "core/renderer/RenderCommand.h"
#include "core/renderer/OrthorgraphicCamera.h"
#include "core/renderer/RendererID.h"
#include "core/renderer/Shader.h"

namespace CherryBell {

	class Renderer
	{
	public:
		static void BeginScene(OrthorgraphicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData _sceneData;
	};
}