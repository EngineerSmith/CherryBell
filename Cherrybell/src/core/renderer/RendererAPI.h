#pragma once
#include "core/renderer/VertexArray.h"
#include "core/renderer/DrawType.h"
#include <glm/glm.hpp>

namespace CherryBell {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,
		};
	public:
		static Scope<RendererAPI> Create();
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, const DrawType type) = 0;

		inline static API GetAPI() { return s_api; };
	private:
		static API s_api;
	};
}
