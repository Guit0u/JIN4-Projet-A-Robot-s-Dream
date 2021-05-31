#include "myMain.h"


#define windowHeight 800
#define windowWidth 800


using namespace std;

void loadLevel(b2World& world, Level& level, Player& player, sf::RenderWindow &window, char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);
	if (!result)
	{
        std::cerr << "Could not open file leveltest.xml because " << result.description() << std::endl;
        return;
	}
	pugi::xml_node levelData = doc.child("LevelData");

	level.load(world, levelData,window);

	pugi::xml_node playerNode = levelData.child("Player");
	b2Vec2 playerPos = b2Vec2(playerNode.attribute("x").as_float(), playerNode.attribute("y").as_float());
	player.setposition(playerPos);

}

int myMain()
{
	//define window
	sf::RenderWindow window(sf::VideoMode(windowHeight, windowWidth), "test platforme");
	window.setFramerateLimit(60);

	// Define box2d world
	b2Vec2 gravity(0.0f, -20.0f);
	b2World world(gravity);

	

	//define level
	Level level;

	ContactListener contactListener(level);
	world.SetContactListener(&contactListener);

	//define player
	Player player(world, { 0.0f, 0.0f });

	loadLevel(world, level, player, window, "resources/leveltest.xml");

	
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				level.setNextLine();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				loadLevel(world, level, player, window, "resources/leveltest.xml");
				level.addPressurePlate(world,b2Vec2(-50.0f, 0.1f), b2Vec2(10.0f,2.0f),"Red", 5);
			}

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