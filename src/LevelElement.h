#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

class LevelElement
{
public:
	explicit LevelElement(std::string const& textureFile);
	virtual ~LevelElement() = default;

	b2Body* getBodyPointer();
	void setBodyPointer(b2Body* ptr);
	//sf::Color getColor();

	virtual void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);
	virtual bool interract(); // used for switch only
	virtual void setElementState(int id, int state); // used for door only

private:
	b2Body* body = nullptr;

protected:
	sf::Texture texture;
	sf::Sprite sprite;
};
