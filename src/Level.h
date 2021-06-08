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
#include "Door.h"

#include "DialogueBox.h"

#include "Enigme.h"
#include "EnigmeTuyaux.h"
#include "EnigmeLink.h"


/*
Class containing the physic structure of the world (do not do the calculation), 
the enigmes and the dialogue
*/
class Level
{
public:
	explicit Level() = default;

	// interacting with the Level
	void load(b2World& world, pugi::xml_node node, sf::RenderWindow &window);
	bool setNextLine();
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);

	// adding LevelElement
	void addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color);
	void addDynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& color);
	void addPressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId);
	void addSwitch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId, int nbState);
	void addDoor(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int id);

	// adding Enigme
	void addEnigmeTuyaux(int outputId, pugi::xml_node node);
	void addEnigmeLink(int inputId, int condValue, int outputId);

	// interacting with enigmes
	void enigmeInput(int id, int value) const;
	bool checkEnigme();
	void activateSwitchs();
	void openDoor(int id, int state);

	// testing methode
	int getNbElements() const;
	int getNbEnigmes() const;
	LevelElement* getElement(int i) const;
	Enigme* getEnigme(int i) const;


private:
	std::vector<std::unique_ptr<LevelElement>> elements;
	std::vector<std::unique_ptr<Enigme>> enigmes;
	DialogueBox dialogue;
};
