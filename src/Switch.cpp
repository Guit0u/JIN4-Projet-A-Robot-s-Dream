#include "Switch.h"



Switch::Switch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId) :
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


void Switch::startContact()
{
	setStateValue(1);
}

void Switch::endContact()
{
	setStateValue(0);
}

void Switch::interract() 
{
	if (getStateValue()) {
		switchState = !switchState;
		printf("tu es sur le levier ça fonctionne\n");
	}
	else {
		printf("tu n'es pas sur le levier\n");
	}
}
