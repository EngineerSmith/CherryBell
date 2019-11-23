#pragma once
#include "core/Core.h"
#include "core/tilemap/Tile.h"

namespace CherryBell {
	using TilemapData = pair_map<std::pair<int, int>, Ref<Tile>>;
	
	class Tilemap
	{
	public:
		Tilemap(const uint16_t width, const uint16_t height);

		void Render();

		TilemapData& GetMap() { return _tilemap; }

		TilemapData::iterator begin() { return _tilemap.begin(); }
		TilemapData::iterator end() { return _tilemap.end(); }
	private:
		const uint16_t _width, _height;
		TilemapData _tilemap;
	};
}
