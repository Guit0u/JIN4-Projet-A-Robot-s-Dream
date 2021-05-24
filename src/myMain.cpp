#include "myMain.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <stdio.h>
#include <assert.h>


#define height 800
#define width 800
#define scale 2

void drawBody(b2Body* body, sf::RenderWindow& window, std::pair<double,double> viewportOffset)
{
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != NULL)
	{
		switch (fixture->GetType())
		{
		case b2Shape::e_polygon:
			{
				b2Vec2 size { 0.0, 0.0 };
				b2Vec2 pos;


				b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
				int32 vertexCount = poly->m_count;

				if (vertexCount == 4)
				{
					pos = poly->m_vertices[0];

					for (int32 i = 1; i < 4; ++i)
					{
						b2Vec2 vertex = poly->m_vertices[i];
						if (vertex.x < pos.x)
						{
							size.x += pos.x - vertex.x;
							pos.x = vertex.x;
						}
						else if (vertex.x > pos.x + size.x)
						{
							size.x += vertex.x - pos.x;
						}

						if (vertex.y < pos.y)
						{
							size.y += pos.y - vertex.y;
							pos.y = vertex.y;
						}
						else if (vertex.y > pos.y + size.y)
						{
							size.y += vertex.y - pos.y;
						}

					}
					pos += body->GetPosition();
					sf::RectangleShape rectangle(sf::Vector2f(size.x, size.y));
					rectangle.setPosition(sf::Vector2f(pos.x-viewportOffset.first, -pos.y-viewportOffset.second));
					rectangle.setFillColor(sf::Color::Green);
					rectangle.setOutlineColor(sf::Color::White);
					rectangle.setOutlineThickness(1);
					window.draw(rectangle);
				}

			}
			break;

		default:
			break;
		}
		fixture = fixture->GetNext();
	}
}


int myMain()
{
	
	// Define box2d world
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);


	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	//define a box on the ground
	b2BodyDef boxDef;
	boxDef.type = b2_dynamicBody;
	boxDef.position.Set(-1.5f, 1.01f);
	b2Body* box = world.CreateBody(&boxDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1.0f, 1.0f);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 2.0f;
	boxFixtureDef.friction = 0.0f;
	box->CreateFixture(&boxFixtureDef);


	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 6.0f);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);


	//define window
	sf::RenderWindow window(sf::VideoMode(width, height), "test platforme");
	window.setFramerateLimit(60);





	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	
	b2Vec2 bodyPosition = body->GetPosition();
	float bodyAngle = body->GetAngle();

	while (window.isOpen())
	{
		//input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			b2Vec2 impulse(-20.0f, 0.0f);
			body->ApplyLinearImpulseToCenter(impulse, true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			b2Vec2 impulse(20.0f, 0.0f);
			body->ApplyLinearImpulseToCenter(impulse, true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			b2Vec2 impulse(0.0f, 20.0f);
			body->ApplyLinearImpulseToCenter(impulse, true);
		}

		//physique
		world.Step(timeStep, velocityIterations, positionIterations);

		//affichage

		bodyPosition = body->GetPosition();
		bodyAngle = body->GetAngle();


		window.clear();

		drawBody(body, window, { -400.0, -400.0 });
		drawBody(box, window, { -400.0, -400.0 });
		drawBody(groundBody, window, { -400.0, -400.0 });

		window.display();
	}
	
	return 0;
}