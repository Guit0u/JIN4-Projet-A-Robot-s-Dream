#pragma once
#include "LevelElement.h"

/*
object subject to physic
Fall and can be pushed around
*/
class DynamicElement : public LevelElement
{
public:
	explicit DynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& color);
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) override;
};
