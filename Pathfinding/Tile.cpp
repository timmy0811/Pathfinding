#include "Tile.h"

Tile::Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size)
	:gridPos(gridPos), size(size), globalPos(globalPos)
{
	this->color = sf::Color::White;

	this->vertex[0].position = sf::Vector2f(static_cast<float>(this->globalPos.x), static_cast<float>(this->globalPos.y));
	this->vertex[1].position = sf::Vector2f(static_cast<float>(this->globalPos.x + this->size), static_cast<float>(this->globalPos.y));
	this->vertex[2].position = sf::Vector2f(static_cast<float>(this->globalPos.x + this->size), static_cast<float>(this->globalPos.y + this->size));
	this->vertex[3].position = sf::Vector2f(static_cast<float>(this->globalPos.x), static_cast<float>(this->globalPos.y + this->size));
}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(this->vertex, 4, sf::Quads);
}

void Tile::setColor(sf::Color)
{
	this->color = color;
}
