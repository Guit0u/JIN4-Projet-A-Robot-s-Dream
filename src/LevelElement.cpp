#include "LevelElement.h"
#include <iostream>


LevelElement::LevelElement(std::string const& textureFile)
{
	bool result = texture.loadFromFile(textureFile);
	if (!result) {
		std::cerr << "coudl not load file" << textureFile << std::endl;
	}
}


b2Body* LevelElement::getBodyPointer()
{
	return body;
}

void LevelElement::setBodyPointer(b2Body* ptr)
{
	body = ptr;
}


void LevelElement::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	sprite.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
	window.draw(sprite);
}

bool LevelElement::interract() {
	// return false by default
	//only switches have interaction override
	return false;
}

void LevelElement::setElementState(int id, int state)
{
	// do nothing by default
	// only doors have an override
}