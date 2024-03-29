#pragma once
#include "core/renderer/RendererAPI.h"

namespace CherryBell {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawType type) override;
	};
}