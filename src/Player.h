#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

#define playerWidth 10
#define playerHight 10
#define maxSpeed 100
#define horizontalInpulseIntensity 5000
#define verticalInputIntesity 200000

class Player
{
public:
	explicit Player(b2World& world, b2Vec2 pos);

	void processInput();
	void setposition(b2Vec2 pos);
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);

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
};
