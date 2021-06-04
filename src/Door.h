#pragma once
#include "LevelElement.h"

class Door : public LevelElement
{
public:
	Door(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int id);
	
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) override;
	void setElementState(int inId, int state) override;

private:
	bool open = false;
	int id;
};
