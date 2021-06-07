#include "Door.h"

Door::Door(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int id):
	LevelElement(file),
	id(id)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(texture.getSize().x/2, texture.getSize().y/2);


	getBodyPointer()->CreateFixture(&bodyShape, 0.0f);

	sprite.setOrigin(-pos.x + texture.getSize().x/2, pos.y + texture.getSize().y/2);
}

void Door::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	if (!open)
	{
		sprite.setPosition(sf::Vector2f(-viewportOffset.first,- viewportOffset.second));
		window.draw(sprite);
	}
}

void Door::setElementState(int inId, int state)
{
	if (inId == id)
	{
		open = state;
	}
	getBodyPointer()->SetEnabled(!open);
		
}