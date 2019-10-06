#pragma once

#include <glm/glm.hpp>
#include "core/renderer/VertexArray.h"

namespace CherryBell {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_api; };
	private:
		static API s_api;
	};
}