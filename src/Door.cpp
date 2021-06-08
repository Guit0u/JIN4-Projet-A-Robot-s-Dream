#include "Door.h"

constexpr auto WIDTH_FRAME_DOOR = 77;
constexpr auto HEIGHT_FRAME_DOOR = 125;

Door::Door(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int id):
	LevelElement(file),
	id(id)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y+HEIGHT_FRAME_DOOR/2);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(WIDTH_FRAME_DOOR/2, HEIGHT_FRAME_DOOR/2);


	getBodyPointer()->CreateFixture(&bodyShape, 0.0f);
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(-pos.x + WIDTH_FRAME_DOOR/2, pos.y + HEIGHT_FRAME_DOOR);
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