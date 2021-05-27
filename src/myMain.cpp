#include "myMain.h"


#define windowHeight 800
#define windowWidth 800


using namespace std;

pugi::xml_document doc;

void loadLevel(b2World& world, Level& level, Player& player,DialogueBox &dialogue, sf::RenderWindow &window, char* fileName)
{
	
	pugi::xml_parse_result result = doc.load_file(fileName);
	if (!result)
	{
        std::cerr << "Could not open file leveltest.xml because " << result.description() << std::endl;
        return;
	}
	pugi::xml_node levelData = doc.child("LevelData");

	level.load(world, levelData.child("Level"));

	pugi::xml_node playerNode = levelData.child("Player");
	b2Vec2 playerPos = b2Vec2(playerNode.attribute("x").as_float(), playerNode.attribute("y").as_float());
	player.setposition(playerPos);

	//add dilaogue and set font
	pugi::xml_node currNode(levelData.child("dialogue"));
	dialogue.load(currNode, window);
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

	//define player
	Player player(world, { 0.0f, 0.0f });

	DialogueBox dialogue;

	loadLevel(world, level, player, dialogue, window, "resources/leveltest.xml");

	
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
				dialogue.setNextLine();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				loadLevel(world, level, player, dialogue, window, "resources/leveltest.xml");
			}

		}
		
		player.processInput();

		//physique
		world.Step(timeStep, velocityIterations, positionIterations);

		//affichage

		window.clear();

		player.draw(window, { -400.0f, -400.0f });
		level.draw(window, { -400.0f, -400.0f });
		dialogue.display(window);
		window.display();
	}
	
	return 0;
}