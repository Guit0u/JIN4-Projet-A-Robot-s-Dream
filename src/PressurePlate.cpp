#include "PressurePlate.h"

constexpr auto NB_FRAMES_PP= 2;
constexpr auto WIDTH_FRAME_PP = 80;
constexpr auto HEIGHT_FRAME_PP = 20;

PressurePlate::PressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId) :
	LevelElement(file),
	ContactElement(inputId)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((ContactElement*)this);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(WIDTH_FRAME_PP / 2, HEIGHT_FRAME_PP/2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.isSensor = true;
	bodyFixtureDef.filter.maskBits = 0xffff;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, WIDTH_FRAME_PP, HEIGHT_FRAME_PP));
	sprite.setOrigin(-pos.x + WIDTH_FRAME_PP / 2, pos.y+HEIGHT_FRAME_PP/2);
}


void PressurePlate::startContact()
{
	setStateValue(1);
	sprite.setTextureRect(sf::IntRect(WIDTH_FRAME_PP+8, 0, WIDTH_FRAME_PP, HEIGHT_FRAME_PP));
}

void PressurePlate::endContact()
{
	setStateValue(0);
	sprite.setTextureRect(sf::IntRect(0, 0, WIDTH_FRAME_PP, HEIGHT_FRAME_PP));
}
