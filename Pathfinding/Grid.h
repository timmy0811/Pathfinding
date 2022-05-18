#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tile.h"

class Grid
{
private:
	std::vector<Tile*> tiles;
	sf::Vector2i dimensions;

public:
	Grid(sf::Vector2i dimensions, int tileSize);

	void render(sf::RenderTarget* target);
};

