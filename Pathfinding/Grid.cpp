#include "Grid.h"

Grid::Grid(sf::Vector2i dimensions, int tileSize)
	:dimensions(dimensions)
{
	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			this->tiles.push_back(new Tile(sf::Vector2i(x, y), sf::Vector2i(x * tileSize + 1, y * tileSize + 1), 50 - 2));
		}
	}
}

void Grid::render(sf::RenderTarget* target)
{
	for (Tile* tile : this->tiles) {
		tile->render(target);
	}
}
