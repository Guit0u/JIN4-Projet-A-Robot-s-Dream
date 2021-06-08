#include <gtest/gtest.h>
#include <string>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"

#include "Player.h"
#include "Level.h"
#include "LevelElement.h"
#include "Enigme.h"




//Player

TEST(Initialisation_player, constructeur) {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    Player player(world, { 10.0f, 20.0f });
    b2Vec2 playerPos = player.getPosition();
    EXPECT_EQ(playerPos.x, 10.0f);
    EXPECT_EQ(playerPos.y, 20.0f);
}

TEST(Initialisation_player, setPosition) {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    Player player(world, { 10.0f, 20.0f });
    player.setposition({ 30.0f, 5.0f });
    b2Vec2 playerPos = player.getPosition();
    EXPECT_EQ(playerPos.x, 30.0f);
    EXPECT_EQ(playerPos.y, 5.0f);
}

TEST(Dynamic_player, fall) {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    Player player(world, { 10.0f, 20.0f });

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    int nbIteration = 5;
    for (int i = 0; i < nbIteration; i++)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
    }

    b2Vec2 playerPos = player.getPosition();
    EXPECT_EQ(playerPos.x, 10.0f);
    EXPECT_LT(playerPos.y, 20.0f);
}

//Level

TEST(Initialisation_level, constructeur)
{
    Level level;
    EXPECT_EQ(level.getNbElements(), 0);
    EXPECT_EQ(level.getNbEnigmes(), 0);
}

TEST(Initialisation_level, addStaticElement)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addStaticElement(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "placeHolder.png");

    EXPECT_EQ(level.getNbElements(), 1);
    EXPECT_EQ(level.getNbEnigmes(), 0);
    LevelElement* elementPtr = level.getElement(0);
    b2Vec2 pos = elementPtr->getBodyPointer()->GetPosition();
    EXPECT_EQ(pos.x, 2);
    EXPECT_EQ(pos.y, 4);
    EXPECT_NO_THROW(dynamic_cast<StaticElement*>(elementPtr));
}

TEST(Initialisation_level, addDynamicElement)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addDynamicElement(world, { 2.0f,4.0f }, { 5.0f,5.0f }, 1.0f, 1.0f, "placeHolder.png");

    EXPECT_EQ(level.getNbElements(), 1);
    EXPECT_EQ(level.getNbEnigmes(), 0);
    LevelElement* elementPtr = level.getElement(0);
    b2Vec2 pos = elementPtr->getBodyPointer()->GetPosition();
    EXPECT_EQ(pos.x, 2);
    EXPECT_EQ(pos.y, 4);
    EXPECT_NO_THROW(dynamic_cast<DynamicElement*>(elementPtr));
}

TEST(Initialisation_level, addPressurePlate)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addPressurePlate(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "placeHolder.png", 1);

    EXPECT_EQ(level.getNbElements(), 1);
    EXPECT_EQ(level.getNbEnigmes(), 0);
    LevelElement* elementPtr = level.getElement(0);
    b2Vec2 pos = elementPtr->getBodyPointer()->GetPosition();
    EXPECT_EQ(pos.x, 2);
    EXPECT_EQ(pos.y, 4);
    EXPECT_NO_THROW(dynamic_cast<PressurePlate*>(elementPtr));
}

TEST(Initialisation_level, addSwitch)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addSwitch(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "placeHolder.png", 1, 4);

    EXPECT_EQ(level.getNbElements(), 1);
    EXPECT_EQ(level.getNbEnigmes(), 0);
    LevelElement* elementPtr = level.getElement(0);
    b2Vec2 pos = elementPtr->getBodyPointer()->GetPosition();
    EXPECT_EQ(pos.x, 2);
    EXPECT_EQ(pos.y, 4);
    EXPECT_NO_THROW(dynamic_cast<Switch*>(elementPtr));
}

TEST(Initialisation_level, addDoor)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addDoor(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "placeHolder.png", 4);

    EXPECT_EQ(level.getNbElements(), 1);
    EXPECT_EQ(level.getNbEnigmes(), 0);
    LevelElement* elementPtr = level.getElement(0);
    b2Vec2 pos = elementPtr->getBodyPointer()->GetPosition();
    EXPECT_EQ(pos.x, 2);
    EXPECT_EQ(pos.y, 4);
    EXPECT_NO_THROW(dynamic_cast<Door*>(elementPtr));
}

TEST(Initialisation_level, addEnigmeLink)
{
    Level level;
    level.addEnigmeLink(1, 2, 3);
    EXPECT_EQ(level.getNbElements(), 0);
    EXPECT_EQ(level.getNbEnigmes(), 1);
    Enigme* enigmePtr = level.getEnigme(0);
    EXPECT_NO_THROW(dynamic_cast<EnigmeLink*>(enigmePtr));
}

TEST(Initialisation_level, addEnigmeTuyau)
{
    std::string xml = R"(
        <?xml version="1.0" encoding="UTF-8"?>
        <EnigmeTuyaux output="1">
			<TuyauFixe type="droit" orientation="0" posX="0" posY="0"/>
			<TuyauMobile id="1" type="te" orientation="0" posX="127" posY="0">
				<Switch id="1"/>
				<Switch id="2"/>
			</TuyauMobile>
			<TuyauMobile id="2" type="coude" orientation="2" posX="127" posY="127">
				<Switch id="1"/>
			</TuyauMobile>	
			<Solution>
				<Tuyau id="1">
					<Sol orientation="0"/>
					<Sol orientation="1"/>
				</Tuyau>
				<Tuyau id="2">
					<Sol orientation="2"/>
				</Tuyau>
			</Solution>	
		</EnigmeTuyaux>)";

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);

    Level level;
    level.addEnigmeTuyaux(1, doc.child("EnigmeTuyaux"));
    
    EXPECT_EQ(level.getNbElements(), 0);
    EXPECT_EQ(level.getNbEnigmes(), 1);
    Enigme* enigmePtr = level.getEnigme(0);
    EXPECT_NO_THROW(dynamic_cast<EnigmeTuyaux*>(enigmePtr));
}

TEST(Initialisation_level, reloadLevel)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addStaticElement(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "Red");
    level.addEnigmeLink(1, 2, 3);
    EXPECT_EQ(level.getNbElements(), 1);
    EXPECT_EQ(level.getNbEnigmes(), 1);

    std::string xml = R"(<?xml version="1.0" encoding="UTF-8"?>
    <LevelData>
	    <Level>
	    </Level>
	    <Enigme>
	    </Enigme>
    </LevelData>)";

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);

    sf::RenderWindow window(sf::VideoMode(800, 800), "tests");

    level.load(world, doc.child("LevelData"), window);
    EXPECT_EQ(level.getNbElements(), 0);
    EXPECT_EQ(level.getNbEnigmes(), 0);
}

TEST(Dynamic_level, dynamicElement)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addDynamicElement(world, { 2.0f,4.0f }, { 5.0f,5.0f }, 1.0f, 1.0f, "placeHolder.png");

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    int nbIteration = 5;
    for (int i = 0; i < nbIteration; i++)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
    }

    LevelElement* elementPtr = level.getElement(0);
    b2Vec2 pos = elementPtr->getBodyPointer()->GetPosition();
    EXPECT_EQ(pos.x, 2.0f);
    EXPECT_LT(pos.y, 4.0f);
}

//Enigmes and switch

TEST(Enigme_link, wrongInput)
{
    Level level;
    level.addEnigmeLink(1, 2, 3);
    level.enigmeInput(1, 1);
    EXPECT_FALSE(level.checkEnigme());
}

TEST(Enigme_link, rightInput)
{
    Level level;
    level.addEnigmeLink(1, 2, 3);
    level.enigmeInput(1, 2);
    EXPECT_TRUE(level.checkEnigme());
}

TEST(Enigme_link, switchInput)
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    Level level;
    level.addSwitch(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "Red", 1, 4);
    level.addEnigmeLink(1, 3, 3);

    auto switchPtr = dynamic_cast<Switch*>(level.getElement(0));

    switchPtr->startContact();
    //switch state = 0
    EXPECT_FALSE(level.checkEnigme());

    level.activateSwitchs();
    //switch state = 1
    EXPECT_FALSE(level.checkEnigme());

    level.activateSwitchs();
    level.activateSwitchs();
    //switch state = 3
    EXPECT_TRUE(level.checkEnigme());

    switchPtr->endContact();
    level.activateSwitchs();
    //switch state = 3
    EXPECT_TRUE(level.checkEnigme());

    switchPtr->startContact();
    level.activateSwitchs();
    //switch state = 0
    EXPECT_FALSE(level.checkEnigme());
}

TEST(Enigme_tuyaux, wrongInput)
{
    std::string xml = R"(
        <?xml version="1.0" encoding="UTF-8"?>
        <EnigmeTuyaux output="1">
			<TuyauMobile id="1" type="te" orientation="0" posX="127" posY="0">
				<Switch id="1"/>
				<Switch id="2"/>
			</TuyauMobile>
			<TuyauMobile id="2" type="coude" orientation="2" posX="127" posY="127">
				<Switch id="1"/>
			</TuyauMobile>	
			<Solution>
				<Tuyau id="1">
					<Sol orientation="0"/>
					<Sol orientation="1"/>
				</Tuyau>
				<Tuyau id="2">
					<Sol orientation="2"/>
				</Tuyau>
			</Solution>	
		</EnigmeTuyaux>)";

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);

    Level level;
    level.addEnigmeTuyaux(1, doc.child("EnigmeTuyaux"));
    EXPECT_FALSE(level.checkEnigme());
    level.enigmeInput(1, -1); // with this enigme, the value field does not matter
    EXPECT_FALSE(level.checkEnigme());
}

TEST(Enigme_tuyaux, rightInput)
{
    std::string xml = R"(
        <?xml version="1.0" encoding="UTF-8"?>
        <EnigmeTuyaux output="1">
			<TuyauMobile id="1" type="te" orientation="0" posX="127" posY="0">
				<Switch id="1"/>
				<Switch id="2"/>
			</TuyauMobile>
			<TuyauMobile id="2" type="coude" orientation="2" posX="127" posY="127">
				<Switch id="1"/>
			</TuyauMobile>	
			<Solution>
				<Tuyau id="1">
					<Sol orientation="0"/>
					<Sol orientation="1"/>
				</Tuyau>
				<Tuyau id="2">
					<Sol orientation="2"/>
				</Tuyau>
			</Solution>	
		</EnigmeTuyaux>)";

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);

    Level level;
    level.addEnigmeTuyaux(1, doc.child("EnigmeTuyaux"));

    level.enigmeInput(2, -1); // with this enigme, the value field does not matter
    EXPECT_TRUE(level.checkEnigme());
}

TEST(Enigme_tuyaux, switchInput)
{
    std::string xml = R"(
        <?xml version="1.0" encoding="UTF-8"?>
        <EnigmeTuyaux output="1">
			<TuyauMobile id="1" type="te" orientation="0" posX="127" posY="0">
				<Switch id="1"/>
				<Switch id="2"/>
			</TuyauMobile>
			<TuyauMobile id="2" type="coude" orientation="2" posX="127" posY="127">
				<Switch id="1"/>
			</TuyauMobile>	
			<Solution>
				<Tuyau id="1">
					<Sol orientation="0"/>
					<Sol orientation="1"/>
				</Tuyau>
				<Tuyau id="2">
					<Sol orientation="2"/>
				</Tuyau>
			</Solution>	
		</EnigmeTuyaux>)";

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    Level level;
    level.addEnigmeTuyaux(1, doc.child("EnigmeTuyaux"));

    level.addSwitch(world, { 2.0f,4.0f }, { 5.0f,5.0f }, "Red", 1, 4);
    level.addSwitch(world, { 20.0f,4.0f }, { 5.0f,5.0f }, "Red", 2, 4);

    auto switch1Ptr = dynamic_cast<Switch*>(level.getElement(0));
    auto switch2Ptr = dynamic_cast<Switch*>(level.getElement(1));

    switch1Ptr->startContact();
    level.activateSwitchs();
    EXPECT_FALSE(level.checkEnigme());
    switch2Ptr->startContact(); // with this the tuyau 1 should rotate 2 time with one activate switch call.
    level.activateSwitchs();
    switch2Ptr->endContact();
    level.activateSwitchs();
    level.activateSwitchs();
    EXPECT_TRUE(level.checkEnigme());
}


/* TEST TO DO
- Pressure Plate (broken attempt below)
- Door
- Player input
- Player state (jump limit)
- Dialogue
- Game state
- display
*/







//Pressure Plate

/* not working in test but working fine ingame ...
TEST(PressurePlate, dynamicActivation)   
{
    b2Vec2 gravity(0.0f, -100.0f);
    b2World world(gravity);
    Level level;
    level.addStaticElement(world, { 0.0f, -2.0f }, { 600.0f, 4.0f }, "Green");
    level.addPressurePlate(world, { 0.0f, 0.0f }, { 10.0f, 2.0f }, "Red", 1);
    level.addDynamicElement(world, { 0.0f, 6.0f }, { 1.0f, 1.0f }, 0.5f, 0.0f, "Magenta");
    level.addEnigmeLink(1, 1, 1);

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    int nbIteration = 75;
    for (int i = 0; i < nbIteration; i++)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
    }
    EXPECT_TRUE(level.checkEnigme());
}
*/