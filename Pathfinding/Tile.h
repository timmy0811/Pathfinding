#pragma once

#include <SFML/Graphics.hpp>

enum class tileState { WALL , DEFAULT};

class Tile
{
private:
	sf::Vector2i gridPos;
	sf::Vector2i globalPos;

	const int size;
	tileState state;

	sf::Vertex* vertex[4];
	sf::Color color;

public:
	Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size);

	void render(sf::RenderTarget* target);

	void setState(tileState state);
	void setColor(sf::Color color);
	void changeColor(sf::Color color);

	sf::Vector2i getPosition();
};

