#pragma once
#include "core/renderer/DrawType.h"
#include "core/renderer/OrthorgraphicCamera.h"
#include "core/renderer/Texture.h"

namespace CherryBell {
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthorgraphicCamera& camera);
		static void EndScene();

		// Primitives

		static void FillQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color);
		static void FillQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color);

		static void LineQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color);
		static void LineQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color);

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const DrawType drawType = DrawType::Fill);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const Ref<Texture2D>& texture, const DrawType drawType = DrawType::Fill);
	};
}
