#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <vector>

#include "LevelElement.h"
#include "StaticElement.h"
#include "DynamicElement.h"

class Level
{
public:
	explicit Level() = default;

	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);
	void addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, sf::Color color);
	void addDynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, sf::Color color);

private:
	std::vector<std::unique_ptr<LevelElement>> elements;
};
