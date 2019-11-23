#pragma once
#include "core/renderer/Texture.h"
#include "core/Core.h"

#include <glm/glm.hpp>

namespace CherryBell{
	class Tile
	{ 
	public:
		virtual void Render(const glm::vec2& position, const glm::vec2& size) = 0;
	};

	class TexturedTile : public Tile
	{
	public:
		TexturedTile(Ref<Texture2D> texture);

		void Render(const glm::vec2& position, const glm::vec2& size) override;
	private:
		Ref<Texture2D> _texture;
	};

	//TODO
	class AnimatedTile : public Tile
	{
	public:
		void Render(const glm::vec2& position, const glm::vec2& size) override { CB_CORE_NOT_IMPLEMENTED(); }
	};
}
