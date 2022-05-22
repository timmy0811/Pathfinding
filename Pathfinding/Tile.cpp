#include "Tile.h"

void Tile::reset()
{
	this->f_Cost = 0;
	this->g_Cost = 0;
	this->h_Cost = 0;

	this->visited = false;
	if (this->state != tileState::WALL) {
		this->state = tileState::DEFAULT;
	}
}

Tile::Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size)
	:gridPos(gridPos), size(size), globalPos(globalPos)
{
	this->color = sf::Color::White;
	this->state = tileState::DEFAULT;

	this->f_Cost = 0;
	this->g_Cost = 0;
	this->h_Cost = 0;

	this->visited = false;

	this->vertex[0].position = sf::Vector2f(static_cast<float>(this->globalPos.x), static_cast<float>(this->globalPos.y));
	this->vertex[1].position = sf::Vector2f(static_cast<float>(this->globalPos.x + this->size), static_cast<float>(this->globalPos.y));
	this->vertex[2].position = sf::Vector2f(static_cast<float>(this->globalPos.x + this->size), static_cast<float>(this->globalPos.y + this->size));
	this->vertex[3].position = sf::Vector2f(static_cast<float>(this->globalPos.x), static_cast<float>(this->globalPos.y + this->size));
}

void Tile::render(sf::RenderTarget* target)
{
	switch (this->state) {
	case tileState::WALL:
		this->changeColor(sf::Color::Blue);
		break;
	case tileState::START:
		this->changeColor(sf::Color::Red);
		break;
	case tileState::PATH:
		this->changeColor(sf::Color::Green);
		break;
	case tileState::END:
		this->changeColor(sf::Color::Magenta);
		break;
	case tileState::SEEN:
		this->changeColor(sf::Color::Yellow);
		break;
	case tileState::DEFAULT:
		this->changeColor(sf::Color::White);
		break;	

	}

	target->draw(this->vertex, 4, sf::Quads);
}

void Tile::setColor(sf::Color color)
{
	this->color = color;
}

void Tile::setGCost(int cost)
{
	this->g_Cost = cost;
}

void Tile::setAsVisited()
{
	this->visited = true;
}

bool Tile::isVisited()
{
	return this->visited;
}

unsigned int Tile::getHCost()
{
	return this->h_Cost;
}

unsigned int Tile::getGCost()
{
	return this->g_Cost;
}

unsigned int Tile::getFCost()
{
	this->f_Cost = this->h_Cost + this->g_Cost;
	return f_Cost;
}

tileState Tile::getState()
{
	return this->state;
}

void Tile::changeColor(sf::Color color)
{
	for (int i = 0; i < 4; i++) {
		sf::Vertex* vert = &(this->vertex[i]);
		vert->color = color;
	}
}

void Tile::calculateHCost(sf::Vector2i endNode)
{
	int xDist = std::abs(this->gridPos.x - endNode.x);
	int yDist = std::abs(this->gridPos.y - endNode.y);
	int remaining = std::abs(xDist - yDist);
	this->h_Cost = MOVE_DIAGONAL_COST * std::min(xDist, yDist) + MOVE_DIRECT_COST * remaining;
}

sf::Vector2i Tile::getPosition()
{
	return this->globalPos;
}

sf::Vector2i Tile::getGridPosition()
{
	return this->gridPos;
}

void Tile::setState(tileState state)
{
	this->state = state;
}
