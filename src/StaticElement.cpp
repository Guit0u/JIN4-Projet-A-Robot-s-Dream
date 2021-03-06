#include "StaticElement.h"

StaticElement::StaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file) :
	LevelElement(file)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y / 2);

	getBodyPointer()->CreateFixture(&bodyShape, 0.0f);

	//set sprite
	sprite = sf::Sprite(texture);
	sprite.setOrigin(pos.x + size.x/2, pos.y+size.y/2);
}
