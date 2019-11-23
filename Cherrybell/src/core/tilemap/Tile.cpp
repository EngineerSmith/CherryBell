#include "cbpch.h"
#include "Tile.h"
#include "core/renderer/Renderer2D.h"

namespace CherryBell {
	TexturedTile::TexturedTile(Ref<Texture2D> texture)
		: _texture(texture)
	{ }

	void TexturedTile::Render(const glm::vec2& position, const glm::vec2& size)
	{
		Renderer2D::FillQuad(position, size, 0, {1,0,0,1}, _texture);
	}
}
