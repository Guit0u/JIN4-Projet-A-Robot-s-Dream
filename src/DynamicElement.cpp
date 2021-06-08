#include "DynamicElement.h"

DynamicElement::DynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& file) :
	LevelElement(file)
{
	// classic constructor for a physic element
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

	// sprite setup
	sprite = sf::Sprite(texture, sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(-pos.x, pos.y);
}

void DynamicElement::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	b2Fixture* fixture =getBodyPointer()->GetFixtureList();

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
	convex.setFillColor(sf::Color::Blue);
	convex.setOutlineColor(sf::Color::White);
	convex.setOutlineThickness(0);
	window.draw(convex);
	sprite.setPosition(sf::Vector2f(getBodyPointer()->GetPosition().x - viewportOffset.first, -getBodyPointer()->GetPosition().y - viewportOffset.second));
	window.draw(sprite);
}