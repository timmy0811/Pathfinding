#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
private:
	sf::Vector2i gridPos;
	sf::Vector2i globalPos;

	const int size;

	sf::Vertex vertex[4];
	sf::Color color;

public:
	Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size);

	void render(sf::RenderTarget* target);
	void setColor(sf::Color);
};

