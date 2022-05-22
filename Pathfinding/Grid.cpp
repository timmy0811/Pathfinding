#include "Grid.h"

void Grid::resetAll()
{
	for (Tile* tile : this->tiles) {
		tile->reset();
		this->visitedTiles.clear();
		this->pastGCost = 0;
	}
}

Grid::Grid(sf::Vector2i dimensions, int tileSize, bool showLable)
	:dimensions(dimensions), tileSize(tileSize), showLable(showLable)
{
	this->pastGCost = 0;
	this->font.loadFromFile("Fonts/Raleway.ttf");

	for (int y = 0; y < dimensions.x; y++) {
		for (int x = 0; x < dimensions.x; x++) {
			this->tiles.push_back(new Tile(sf::Vector2i(x, y), sf::Vector2i(x * tileSize + 1, y * tileSize + 1), 50 - 2));
		}
	}
}

Grid::~Grid()
{
	for (Tile* tile : this->tiles) {
		delete tile;
	}
}

void Grid::render(sf::RenderTarget* target)
{
	for (Tile* tile : this->tiles) {
		tile->render(target);
		if (this->showLable) {
			sf::Text gText;
			gText.setFont(this->font);
			gText.setString(std::to_string(tile->getGCost()));
			gText.setCharacterSize(12);
			gText.setFillColor(sf::Color::Black);
			gText.setPosition(sf::Vector2f(tile->getPosition().x + 1, tile->getPosition().y + 1));

			sf::Text fText;
			fText.setFont(this->font);
			fText.setString(std::to_string(tile->getFCost()));
			fText.setCharacterSize(20);
			fText.setFillColor(sf::Color::Black);
			fText.setPosition(sf::Vector2f(tile->getPosition().x + 11, tile->getPosition().y + 11));

			sf::Text hText;
			hText.setFont(this->font);
			hText.setString(std::to_string(tile->getHCost()));
			hText.setCharacterSize(12);
			hText.setFillColor(sf::Color::Black);
			hText.setPosition(sf::Vector2f(tile->getPosition().x + 30, tile->getPosition().y + 30));

			target->draw(gText);
			target->draw(fText);
			target->draw(hText);
		}
	}
}

Tile* Grid::getIntersectingTile(sf::Vector2f position)
{
	for (Tile* tile : this->tiles) {
		sf::Vector2i pos = tile->getPosition();
		if (position.x > pos.x && position.x < pos.x + tileSize && position.y > pos.y && position.y < pos.y + tileSize) {
			return tile;
		}
	}
	return nullptr;
}

Tile* Grid::getTileByIndex(int xInd, int yInd)
{
	if (xInd < 0 || yInd < 0 || xInd >= this->dimensions.x || yInd >= this->dimensions.y) return nullptr;
	unsigned int vecIndex = this->dimensions.y * yInd + xInd;
	return this->tiles[vecIndex];
}

void Grid::changeState(Tile* tile, tileState state)
{
	for (Tile* tileList : this->tiles) {
		if (tileList == tile) {
			tileList->setState(state);
		}
	}
}

void Grid::findPath(sf::Vector2i startNode, sf::Vector2i endNode)
{
	if(this->visitedTiles.size()) this->resetAll();
	Tile* currentNode = this->getTileByIndex(startNode.x, startNode.y);
	this->pastGCost = 0;
	currentNode->setGCost(0);
	currentNode->setState(tileState::START);

	currentNode->setColor(sf::Color::Blue);
	this->getTileByIndex(endNode.x, endNode.y)->setColor(sf::Color::Red);

	// Main loop for pathfinding
	do {
		std::vector<Tile*> neighbors;

		// Get neighbors
		sf::Vector2i currNodePos = currentNode->getGridPosition();
		neighbors.push_back(this->getTileByIndex(currNodePos.x - 1, currNodePos.y - 1));
		neighbors.push_back(this->getTileByIndex(currNodePos.x	  , currNodePos.y - 1));
		neighbors.push_back(this->getTileByIndex(currNodePos.x + 1, currNodePos.y - 1));
		neighbors.push_back(this->getTileByIndex(currNodePos.x + 1, currNodePos.y	 ));
		neighbors.push_back(this->getTileByIndex(currNodePos.x + 1, currNodePos.y + 1));
		neighbors.push_back(this->getTileByIndex(currNodePos.x	  , currNodePos.y + 1));
		neighbors.push_back(this->getTileByIndex(currNodePos.x - 1, currNodePos.y + 1));
		neighbors.push_back(this->getTileByIndex(currNodePos.x - 1, currNodePos.y	 ));

		Tile* nextNode = nullptr;
		int lowestCost = INT_MAX;
		for (Tile* neighborNode : neighbors) {
			if (!neighborNode || neighborNode->isVisited() || neighborNode->getState() == tileState::WALL) continue;
			neighborNode->setState(tileState::SEEN);
			neighborNode->calculateHCost(endNode);

			if (std::abs(neighborNode->getPosition().x) > 0 && std::abs(neighborNode->getPosition().y) > 0) {
				neighborNode->setGCost(this->pastGCost + MOVE_DIAGONAL_COST);
			}
			else {
				neighborNode->setGCost(this->pastGCost + MOVE_DIRECT_COST);
			}

			if (neighborNode->getFCost() < lowestCost) {
				lowestCost = neighborNode->getFCost();
				nextNode = neighborNode;
			}

			neighborNode->setAsVisited();
			this->visitedTiles.push_back(neighborNode);
		}
		currentNode->setAsVisited();
	
		neighbors.clear();

		this->pastGCost = nextNode->getGCost();
		currentNode = nextNode;
		currentNode->setState(tileState::PATH);

	} while (currentNode->getGridPosition() != endNode);
	this->getTileByIndex(endNode.x, endNode.y)->setState(tileState::END);
}
