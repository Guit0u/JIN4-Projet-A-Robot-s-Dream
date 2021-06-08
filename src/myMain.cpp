#include "myMain.h"


#define windowHeight 800
#define windowWidth 800


using namespace std;

void loadLevel(b2World& world, Level& level, Player& player, sf::RenderWindow &window, int levelNumber)
{
	std::string stringName = "resources/level" + std::to_string(levelNumber) + ".xml";
	const char* charName = stringName.c_str();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(charName);
	if (!result)
	{
        std::cerr << "Could not open file " << stringName << " because " << result.description() << std::endl;
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
	GameState gamestate = GameState::gameplay;
	int curLevel = 3;

	//define window
	sf::RenderWindow window(sf::VideoMode(windowHeight, windowWidth), "test platforme");
	window.setFramerateLimit(60);

	// Define box2d world
	b2Vec2 gravity(0.0f, -100.0f);
	b2World world(gravity);

	

	//define level
	Level level;

	ContactListener contactListener(level);
	world.SetContactListener(&contactListener);

	//define player
	Player player(world, { 0.0f, 0.0f });

	loadLevel(world, level, player, window, curLevel);

	
	// Prepare for simulation. Time step of 1/60 of a second 
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
			if (gamestate == GameState::dialogue && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				if(level.setNextLine()) {
					gamestate = GameState::gameplay;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				loadLevel(world, level, player, window, curLevel);
				gamestate = GameState::gameplay;
			}
			if (gamestate == GameState::gameplay && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
				level.activateSwitchs();
			}

		}

		if (gamestate == GameState::gameplay)
		{
			player.processInput();
		}

		if (level.checkEnigme())
		{
			if (gamestate == GameState::gameplay && !level.setNextLine())
				gamestate = GameState::dialogue;
		}
		
		//physique
		world.Step(timeStep, velocityIterations, positionIterations);

		//affichage

		window.clear();

		level.draw(window, { -400.0f, -400.0f });
		player.draw(window, { -400.0f, -400.0f });
		window.display();

		//passer au niveau suivant quand le joueur sort de la fenêtre par la droite
		if (player.getPosition().x > 400)
		{
			curLevel++;
			loadLevel(world, level, player, window, curLevel);
		}
	}
	
	return 0;
}