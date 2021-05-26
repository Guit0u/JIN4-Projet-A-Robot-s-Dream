#include "StaticElement.h"

StaticElement::StaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, sf::Color color) :
	LevelElement(color)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y / 2);


	getBodypointer()->CreateFixture(&bodyShape, 0.0f);
}
