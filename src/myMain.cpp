#include "myMain.h"


#define windowHeight 800
#define windowWidth 800

void drawBody(b2Body* body, sf::RenderWindow& window, std::pair<double,double> viewportOffset)
{
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != NULL)
	{
		switch (fixture->GetType())
		{
		case b2Shape::e_polygon:
			{
				b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
				int32 vertexCount = poly->m_count;

				if (vertexCount >= 3)
				{
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
	b2Vec2 gravity(0.0f, -20.0f);
	b2World world(gravity);

	/*
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -2.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(300.0f, 2.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	//define a box on the ground
	b2BodyDef boxDef;
	boxDef.type = b2_dynamicBody;
	boxDef.position.Set(-1.5f, 5.01f);

	b2Body* box = world.CreateBody(&boxDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(5.0f, 5.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 0.5f;
	boxFixtureDef.friction = 0.0f;

	box->CreateFixture(&boxFixtureDef);
	*/

	//define level
	Level level;
	level.addStaticElement(world, b2Vec2(0.0f, -2.0f), b2Vec2(600.0f, 4.0f));
	level.addDynamicElement(world, b2Vec2(-1.5f, 5.01f), b2Vec2(10.0f, 10.0f), 0.5f, 0.0f);

	//define player
	Player player(world);

	//define window
	sf::RenderWindow window(sf::VideoMode(windowHeight, windowWidth), "test platforme");
	window.setFramerateLimit(60);





	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	while (window.isOpen())
	{
		//input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.processInput();

		//physique
		world.Step(timeStep, velocityIterations, positionIterations);

		//affichage

		window.clear();

		player.draw(window, { -400.0, -400.0 });
		/*
		drawBody(box, window, { -400.0, -400.0 });
		drawBody(groundBody, window, { -400.0, -400.0 });
		*/
		level.draw(window, { -400.0, -400.0 });
		window.display();
	}
	
	return 0;
}