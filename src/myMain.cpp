#include "myMain.h"


#define windowHeight 800
#define windowWidth 800

int myMain()
{
	
	// Define box2d world
	b2Vec2 gravity(0.0f, -20.0f);
	b2World world(gravity);

	//define level
	Level level;
	level.addStaticElement(world, b2Vec2(0.0f, -2.0f), b2Vec2(600.0f, 4.0f), sf::Color::Blue);
	level.addDynamicElement(world, b2Vec2(-1.5f, 5.01f), b2Vec2(10.0f, 10.0f), 0.5f, 0.0f, sf::Color::Magenta);

	//define player
	Player player(world, b2Vec2(0.0f, 20.0f));

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

		player.draw(window, { -400.0f, -400.0f });
		level.draw(window, { -400.0f, -400.0f });
		window.display();
	}
	
	return 0;
}