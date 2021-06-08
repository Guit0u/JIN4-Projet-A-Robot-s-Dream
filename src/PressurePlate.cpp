#include "PressurePlate.h"

PressurePlate::PressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId) :
	LevelElement(file),
	ContactElement(inputId),
	frameSize(size)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((ContactElement*)this); //black magic to make it work

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y/2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.isSensor = true;
	bodyFixtureDef.filter.maskBits = 0xffff;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);

	//set sprite
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(-pos.x + size.x/ 2, pos.y+size.y/2);
}


void PressurePlate::startContact()
{
	setStateValue(getStateValue() + 1);
	sprite.setTextureRect(sf::IntRect(frameSize.x, 0, frameSize.x, frameSize.y));
}

void PressurePlate::endContact()
{
	setStateValue(getStateValue() - 1);
	if (getStateValue() == 0)
	{
		// set visual to not pressed only if there is no object
		sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
	}
	else if (getStateValue() < 0)
	{
		// failsafe
		setStateValue(0);
	}
}
