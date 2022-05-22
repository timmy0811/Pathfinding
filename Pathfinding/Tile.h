#pragma once

#include <SFML/Graphics.hpp>

enum class tileState { WALL , START, END, PATH, SEEN, DEFAULT};

#define MOVE_DIRECT_COST 10
#define MOVE_DIAGONAL_COST 14

class Tile
{
private:
	sf::Vector2i gridPos;
	sf::Vector2i globalPos;

	unsigned int f_Cost;
	unsigned int h_Cost;
	unsigned int g_Cost;

	const int size;
	tileState state;
	bool visited;

	sf::Vertex vertex[4];
	sf::Color color;

public:
	Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size);

	void render(sf::RenderTarget* target);
	void reset();

	void setState(tileState state);
	void setColor(sf::Color color);
	void setGCost(int cost);
	void setAsVisited();

	unsigned int getHCost();
	unsigned int getGCost();
	unsigned int getFCost();
	tileState getState();

	void changeColor(sf::Color color);

	void calculateHCost(sf::Vector2i endNode);

	sf::Vector2i getPosition();
	sf::Vector2i getGridPosition();
	bool isVisited();
};

