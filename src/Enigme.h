#pragma once
#include "pugixml.hpp"
#include "SFML/Graphics.hpp"

/*
parent class for any enigme
*/
class Enigme
{
public:
	explicit Enigme(int doorId);
	virtual ~Enigme() = default;

	virtual void inputEvent(int id, int value) = 0;
	bool hasChanged();
	bool isResolved() const;
	void setResolved(bool isresolved);
	int getDoor() const; 
	virtual void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);

private:
	bool changed = false;
	bool resolved = false;
	int doorId; //id of the door locked by the enigme
};
