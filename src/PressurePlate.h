#pragma once
#include "LevelElement.h"
#include "ContactElement.h"

class PressurePlate : public LevelElement, public ContactElement
{
public:
	explicit PressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId);


	void startContact() override;
	void endContact() override;

	bool isPressurePlate() override;

};
