#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

class LevelElement
{
public:
	explicit LevelElement(sf::Color color);
	virtual ~LevelElement() = default;

	b2Body* getBodypointer();
	void setBodyPointer(b2Body* ptr);

	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);

private:
	b2Body* body = nullptr;
	sf::Color color;
};
