#include "Level.h"

void Level::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(window, viewportOffset);
	}
	
}

void Level::addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, sf::Color color)
{
	auto ptr = std::make_unique<StaticElement>(world, pos, size, color);
	elements.push_back(move(ptr));
}

void Level::addDynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, sf::Color color)
{
	auto ptr = std::make_unique<DynamicElement>(world, pos, size, density, friction, color);
	elements.push_back(move(ptr));
}