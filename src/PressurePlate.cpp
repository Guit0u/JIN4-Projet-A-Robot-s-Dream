#include "PressurePlate.h"



PressurePlate::PressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId) :
	LevelElement(color),
	ContactElement(inputId)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((ContactElement*)this);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y / 2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.isSensor = true;
	bodyFixtureDef.filter.maskBits = 0xffff;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);
}


void PressurePlate::startContact()
{
	setStateValue(1);
}

void PressurePlate::endContact()
{
	setStateValue(0);
}

bool PressurePlate::isPressurePlate() {
	return true;
}