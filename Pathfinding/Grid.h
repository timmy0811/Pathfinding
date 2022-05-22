#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tile.h"

class Grid
{
private:
	std::vector<Tile*> tiles;
	std::vector<Tile*> visitedTiles;
	sf::Vector2i dimensions;

	int tileSize;
	int pastGCost;
	bool showLable;

	sf::Font font;
	void resetAll();

public:
	Grid(sf::Vector2i dimensions, int tileSize, bool showLable = false);
	~Grid();

	void render(sf::RenderTarget* target);
	void changeState(Tile* tile, tileState state);

	void findPath(sf::Vector2i startNode, sf::Vector2i endNode);

	Tile* getIntersectingTile(sf::Vector2f position);
	Tile* getTileByIndex(int xInd, int yInd);
};

