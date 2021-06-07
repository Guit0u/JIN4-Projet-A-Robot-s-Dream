#include "Switch.h"
#include <iostream>

constexpr auto NB_FRAMES_SWITCH = 2;
constexpr auto WIDTH_FRAME_SWITCH = 108;
constexpr auto HEIGHT_FRAME_SWITCH = 55;


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
	bodyShape.SetAsBox(WIDTH_FRAME_SWITCH / 2, HEIGHT_FRAME_SWITCH / 2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.isSensor = true;
	bodyFixtureDef.filter.maskBits = 0xffff;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, WIDTH_FRAME_SWITCH, HEIGHT_FRAME_SWITCH));
	sprite.setOrigin(-pos.x+WIDTH_FRAME_SWITCH/2, pos.y + HEIGHT_FRAME_SWITCH);
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
		if(getStateValue()%2==1)
			sprite.setTextureRect(sf::IntRect(WIDTH_FRAME_SWITCH, 0, WIDTH_FRAME_SWITCH, HEIGHT_FRAME_SWITCH));
		else
			sprite.setTextureRect(sf::IntRect(0, 0, WIDTH_FRAME_SWITCH, HEIGHT_FRAME_SWITCH));
		return true;
	}
	return false;
	
}

void Switch::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	sprite.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
	window.draw(sprite);
};