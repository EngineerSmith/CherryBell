#pragma once
#include "core/renderer/RenderCommand.h"
#include "core/renderer/OrthorgraphicCamera.h"
#include "core/renderer/RendererID.h"
#include "core/renderer/Shader.h"

namespace CherryBell {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthorgraphicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			SceneData(glm::mat4 viewProjectionMatrix)
				: ViewProjectionMatrix(viewProjectionMatrix)
			{}
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> _sceneData;
	};
}