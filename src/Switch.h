#pragma once
#include "LevelElement.h"
#include "ContactElement.h"

class Switch : public LevelElement, public ContactElement
{
public:
	explicit Switch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId);


	void startContact() override;
	void endContact() override;
	void interract() override;

private:
	bool switchState;
};
