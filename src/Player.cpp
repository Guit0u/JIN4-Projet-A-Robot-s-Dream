#include "Player.h"



Player::Player(b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 20.0f);

	body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(playerWidth /2, playerHight /2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
}

void Player::processInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		b2Vec2 impulse(-horizontalInpulseIntensity, 0.0f);
		body->ApplyLinearImpulseToCenter(impulse, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		b2Vec2 impulse(horizontalInpulseIntensity, 0.0f);
		body->ApplyLinearImpulseToCenter(impulse, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		b2Vec2 impulse(0.0f, verticalInputIntesity);
		body->ApplyLinearImpulseToCenter(impulse, true);
	}
}

void Player::draw(sf::RenderWindow& window, std::pair<double, double> viewportOffset)
{
	b2Fixture* fixture = body->GetFixtureList();

	b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
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