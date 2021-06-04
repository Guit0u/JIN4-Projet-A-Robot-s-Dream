#include "Door.h"

Door::Door(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int id):
	LevelElement(color),
	id(id)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);

	setBodyPointer(world.CreateBody(&bodyDef));

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y / 2);


	getBodyPointer()->CreateFixture(&bodyShape, 0.0f);
}

void Door::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	if (!open)
	{
		b2Fixture* fixture = getBodyPointer()->GetFixtureList();

		auto const poly = (b2PolygonShape*)fixture->GetShape();
		int32 vertexCount = poly->m_count;

		sf::ConvexShape convex;
		convex.setPointCount(vertexCount);

		for (int32 i = 0; i < vertexCount; ++i)
		{
			b2Vec2 pos = poly->m_vertices[i];
			pos += getBodyPointer()->GetPosition();
			convex.setPoint(i, sf::Vector2f(pos.x, -pos.y));
		}
		convex.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
		convex.setFillColor(getColor());
		convex.setOutlineColor(sf::Color::White);
		convex.setOutlineThickness(0);
		window.draw(convex);
	}
}

void Door::setElementState(int inId, int state)
{
	if (inId == id)
	{
		if (state == 1)
		{
			open = true;
		}
		else
		{
			open = false;
		}
	}
	getBodyPointer()->SetAwake(open);
		
}