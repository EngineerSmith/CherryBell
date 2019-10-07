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

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData _sceneData;
	};
}