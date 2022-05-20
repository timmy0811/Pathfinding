#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tile.h"

class Grid
{
private:
	std::vector<Tile*> tiles;
	sf::Vector2i dimensions;
	int tileSize;

public:
	Grid(sf::Vector2i dimensions, int tileSize);
	~Grid();

	void render(sf::RenderTarget* target);
	Tile* getIntersectingTile(sf::Vector2f position);
	void changeState(Tile* tile, tileState state);
};

