#include "DynamicElement.h"

DynamicElement::DynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& file) :
	LevelElement(file)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x/2, size.y/2);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.density = density;
	bodyFixtureDef.friction = friction;

	getBodyPointer()->CreateFixture(&bodyFixtureDef);

	sprite = sf::Sprite(texture, sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(-pos.x + size.x / 2, pos.y+size.y);

	dimensions.first = size.x;
	dimensions.second = size.y;
}

void DynamicElement::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	sprite.setPosition(sf::Vector2f(getBodyPointer()->GetPosition().x + dimensions.first/2 - viewportOffset.first, getBodyPointer()->GetPosition().y - viewportOffset.second));
	window.draw(sprite);
}