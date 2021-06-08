#include "Player.h"


Player::Player(b2World& world, b2Vec2 pos) 
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);	

	body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(playerWidth /2, playerHight /2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 1.f;

	body->CreateFixture(&fixtureDef);
}

void Player::processInput()
{


	if (lastY == body->GetPosition().y && playerState == PlayerState::fall)
	{
		playerState = PlayerState::onGroud;
	}
	else if (lastY > body->GetPosition().y)
	{
		playerState = PlayerState::fall;
	}

	lastY = body->GetPosition().y;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		b2Vec2 impulse(-horizontalInpulseIntensity, 0.0f);
		body->ApplyForceToCenter(impulse, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		b2Vec2 impulse(horizontalInpulseIntensity, 0.0f);
		body->ApplyForceToCenter(impulse, true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerState == PlayerState::onGroud)
	{
		b2Vec2 impulse(0.0f, verticalInputIntesity);
		body->ApplyForceToCenter(impulse, true);
		playerState = PlayerState::jump;
	}

	b2Vec2 velocity = body->GetLinearVelocity();
	if (velocity.LengthSquared() > maxSpeed*maxSpeed)
	{
		velocity.Normalize();
		velocity = b2Vec2(velocity.x * maxSpeed, velocity.y * maxSpeed);
		body->SetLinearVelocity(velocity);
	}
}


void Player::setposition(b2Vec2 pos)
{
	body->SetTransform(pos,0.0f);
	body->SetLinearVelocity({ 0.0f,0.0f });
}


void Player::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
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


b2Vec2 Player::getPosition() const
{
	return body->GetPosition();
}