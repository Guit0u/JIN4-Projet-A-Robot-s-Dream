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
	printf("set active\n");
	active = true;
}

void Switch::endContact()
{
	printf("set inactive\n");
	active = false;
}

bool Switch::interract() 
{
	if (active)
	{
		
		setStateValue((getStateValue() + 1) % nbStates);
		printf("interact switch, new value : %d\n", getStateValue());
		return true;
	}
	return false;
	
}
