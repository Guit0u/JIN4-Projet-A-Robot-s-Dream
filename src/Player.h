#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

#define playerWidth 50
#define playerHight 80


// high values du to physic engine
#define maxSpeed 12000
#define horizontalInpulseIntensity 1000000 
#define verticalInputIntesity 100000000

/*
Class for the object that the use move around with the arrow keys
*/
class Player
{
public:
	explicit Player(b2World& world, b2Vec2 pos);

	void processInput();
	void setposition(b2Vec2 pos);
	void setTexture(sf::Texture const &text);
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);
	b2Vec2 getPosition() const;

private:
	b2Body* body;

	enum class PlayerState
	{
		onGroud,
		jump,
		fall
	};
	PlayerState playerState = PlayerState::onGroud;
	float lastY = 20;
	sf::Texture texture;
	sf::Sprite sprite;
};
