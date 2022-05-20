#include "Grid.h"

Grid::Grid(sf::Vector2i dimensions, int tileSize)
	:dimensions(dimensions), tileSize(tileSize)
{
	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			this->tiles.push_back(new Tile(sf::Vector2i(x, y), sf::Vector2i(x * tileSize + 1, y * tileSize + 1), 50 - 2));
		}
	}
}

Grid::~Grid()
{
	for (Tile* tile : this->tiles) {
		delete tile;
	}
}

void Grid::render(sf::RenderTarget* target)
{
	for (Tile* tile : this->tiles) {
		tile->render(target);
	}
}

Tile* Grid::getIntersectingTile(sf::Vector2f position)
{
	for (Tile* tile : this->tiles) {
		sf::Vector2i pos = tile->getPosition();
		if (position.x > pos.x && position.x < pos.x + tileSize && position.y > pos.y && position.y < pos.y + tileSize) {
			return tile;
		}
	}
	return nullptr;
}

void Grid::changeState(Tile* tile, tileState state)
{
	for (Tile* tileList : this->tiles) {
		if (tileList == tile) {
			tileList->setState(state);
		}
	}
}
