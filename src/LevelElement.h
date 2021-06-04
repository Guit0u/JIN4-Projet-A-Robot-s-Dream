#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

class LevelElement
{
public:
	explicit LevelElement(std::string const& color);
	virtual ~LevelElement() = default;

	b2Body* getBodyPointer();
	void setBodyPointer(b2Body* ptr);

	virtual void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);
	virtual void interract();
private:
	b2Body* body = nullptr;
	std::string color;
};
