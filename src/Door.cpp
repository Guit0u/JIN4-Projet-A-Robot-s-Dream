#include "Door.h"

Door::Door(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int id):
	LevelElement(file),
	id(id)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x/2, size.y/2);


	getBodyPointer()->CreateFixture(&bodyShape, 0.0f);

	//sprite setting
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(-pos.x + size.x/2, pos.y + size.y/2);
}

void Door::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	if (!open)
	{
		sprite.setPosition(sf::Vector2f(-viewportOffset.first,- viewportOffset.second));
		window.draw(sprite);
	}
}

/*
check if the id match and change state acordingly
set/reset corectly the physic state regardless of matching id
*/
void Door::setElementState(int inId, int state)
{
	if (inId == id)
	{
		open = state;
	}
	getBodyPointer()->SetEnabled(!open);
		
}