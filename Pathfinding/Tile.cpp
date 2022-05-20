#include "Tile.h"

Tile::Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size)
	:gridPos(gridPos), size(size), globalPos(globalPos)
{
	this->color = sf::Color::White;
	this->state = tileState::DEFAULT;

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
	case tileState::DEFAULT:
		this->changeColor(sf::Color::Yellow);
		break;	
	}

	target->draw(this->vertex, 4, sf::Quads);
}

void Tile::setColor(sf::Color color)
{
	this->color = color;
}

void Tile::changeColor(sf::Color)
{
	for (sf::Vertex vert : this->vertex) {
		vert.color = color;
	}
}

sf::Vector2i Tile::getPosition()
{
	return this->globalPos;
}

void Tile::setState(tileState state)
{
	this->state = state;
}
