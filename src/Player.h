#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

#define playerWidth 10
#define playerHight 10
#define horizontalInpulseIntensity 50
#define verticalInputIntesity 30

class Player
{
public:
	explicit Player(b2World& world);

	void processInput();
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);

private:
	b2Body* body;
};
