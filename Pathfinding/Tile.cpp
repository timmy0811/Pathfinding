#include "Tile.h"

Tile::Tile(sf::Vector2i gridPos, sf::Vector2i globalPos, int size)
	:gridPos(gridPos), size(size)
{
	this->color = sf::Color::White;

	sf::VertexArray* rect = new sf::VertexArray(sf::Quads, 4);

	(*rect)[0].position = 
}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(this->vertex, 4, sf::Quads);
}

void Tile::setColor(sf::Color)
{
	this->color = color;
}
