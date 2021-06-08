#include "Switch.h"
#include <iostream>


Switch::Switch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId, int nbStates) :
	LevelElement(file),
	ContactElement(inputId),
	nbStates(nbStates),
	frameSize(size)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((ContactElement*)this); // black magic to make it work

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y / 2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.isSensor = true;
	bodyFixtureDef.filter.maskBits = 0xffff;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(-pos.x+size.x/2, pos.y + size.y/2);
}


void Switch::startContact()
{
	active = true;
}

void Switch::endContact()
{
	active = false;
}

/*
methode called when inteacting with a switch
the return value correspond to the active state <=> the state changed when called 
*/
bool Switch::interract() 
{
	if (active)
	{
		setStateValue((getStateValue() + 1) % nbStates);
		if(getStateValue()%2==1)
			sprite.setTextureRect(sf::IntRect(frameSize.x, 0, frameSize.x,frameSize.y));
		else
			sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
		return true;
	}
	return false;
}

void Switch::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	sprite.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
	window.draw(sprite);
};