#pragma once
#include "pugixml.hpp"
#include "SFML/Graphics.hpp"

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
	virtual void draw(sf::RenderWindow& window) = 0;

private:
	bool changed = false;
	bool resolved = false;
	int doorId;
};
