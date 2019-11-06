#pragma once
#include "core/renderer/RendererAPI.h"
#include "core/Core.h"

namespace CherryBell {
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_rendererAPI->Init();
		}

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_rendererAPI->SetViewPort(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawType type = DrawType::Fill)
		{
			s_rendererAPI->DrawIndexed(vertexArray, type);
		}

	private:
		static Scope<RendererAPI> s_rendererAPI;
	};
}