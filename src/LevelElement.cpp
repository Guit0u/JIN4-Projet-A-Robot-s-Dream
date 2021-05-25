#include "LevelElement.h"


LevelElement::LevelElement(float const width, float const height) :
	width(width),
	height(height)
{
}

b2Body* LevelElement::getBodypointer()
{
	return body;
}

void LevelElement::setBodyPointer(b2Body* ptr)
{
	body = ptr;
}


void LevelElement::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	b2Fixture* fixture = body->GetFixtureList();

	auto const poly = (b2PolygonShape*)fixture->GetShape();
	int32 vertexCount = poly->m_count;

	sf::ConvexShape convex;
	convex.setPointCount(vertexCount);

	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 pos = poly->m_vertices[i];
		pos += body->GetPosition();
		convex.setPoint(i, sf::Vector2f(pos.x, -pos.y));
	}
	convex.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
	convex.setFillColor(sf::Color::Green);
	convex.setOutlineColor(sf::Color::White);
	convex.setOutlineThickness(0);
	window.draw(convex);
}