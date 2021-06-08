#pragma once
#include "LevelElement.h"
#include "ContactElement.h"

/*
class representing a object that activate when it enter in contact with a other object
*/
class PressurePlate : public LevelElement, public ContactElement
{
public:
	explicit PressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId);


	void startContact() override;
	void endContact() override;

private:
	b2Vec2 frameSize;
};
