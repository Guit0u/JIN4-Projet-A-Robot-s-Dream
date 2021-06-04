#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "LevelElement.h"
#include "StaticElement.h"
#include "DynamicElement.h"
#include "PressurePlate.h"
#include "Switch.h"
#include "DialogueBox.h"

class Level
{
public:
	explicit Level() = default;

	void load(b2World& world, pugi::xml_node node, sf::RenderWindow &window);
	void setNextLine();
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);

	void addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color);
	void addDynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& color);
	void addPressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId);
	void addSwitch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId);
	void addDoor(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color);

	void enigmeInput(int id, int value) const;
	void checkSwitchs();

private:
	std::vector<std::unique_ptr<LevelElement>> elements;
	DialogueBox dialogue;
};
