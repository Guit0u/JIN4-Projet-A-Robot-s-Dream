#include "Switch.h"
#include <iostream>


Switch::Switch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId, int nbStates) :
	LevelElement(file),
	ContactElement(inputId),
	nbStates(nbStates)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((ContactElement*)this);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(texture.getSize().x / 2, texture.getSize().y / 2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.isSensor = true;
	bodyFixtureDef.filter.maskBits = 0xffff;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);
	sprite.setOrigin(-pos.x + texture.getSize().x/2, pos.y + texture.getSize().y);
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
		setStateValue((getStateValue() + 1) % nbStates);
		sprite.scale(-1.0f, 1.0f);
		sprite.setOrigin(sprite.getPosition().x, -sprite.getPosition().y);
		return true;
	}
	return false;
	
}

void Switch::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	sprite.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
	window.draw(sprite);
};