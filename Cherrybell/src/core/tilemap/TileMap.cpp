#include "cbpch.h"
#include "TileMap.h"
#include "core/renderer/Renderer2D.h"

namespace CherryBell {
	Tilemap::Tilemap(const uint16_t width, const uint16_t height)
		: _width(width), _height(height)
	{ }

	void Tilemap::Render()
	{
		const OrthorgraphicCamera& camera = Renderer2D::GetSceneCamera();
		for (auto kv : _tilemap)
		{
			auto[x, y] = kv.first;
			glm::vec2 position = { x * _width, y * _height }, size = { _width, _height };
			//if (camera.InsideCameraView({ position, 0 }, size))
			{
				CB_CORE_INFO("DRAWING TILE: {0}, {1}", x, y);
				kv.second->Render(position, size);
			}
		}
	}
}
