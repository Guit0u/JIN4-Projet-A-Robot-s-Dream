#pragma once
#include "LevelElement.h"
#include "ContactElement.h"

class Switch : public LevelElement, public ContactElement
{
public:
	explicit Switch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId, int nbStates);


	void startContact() override;
	void endContact() override;
	bool interract() override;
	
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) override;

private:
	int nbStates;
	bool active = false;
};
