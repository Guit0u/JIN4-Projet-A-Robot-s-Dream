#include "Switch.h"



Switch::Switch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId, int nbStates) :
	LevelElement(color),
	ContactElement(inputId),
	nbStates(nbStates)
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
	active = true;
}

void Switch::endContact()
{
	active = false;
}

bool Switch::interract() 
{
	if (active)
	{
		printf("paf interaction");
		setStateValue((getStateValue() + 1) % nbStates);
		return true;
	}
	return false;
	
}
