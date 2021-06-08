#include "Enigme.h"

Enigme::Enigme(int doorId) :
	doorId(doorId)
{}

/*
check if the enigme is considered resolved
*/
bool Enigme::isResolved() const
{
	return resolved;
}

/*
Check if the result of the enigme has change since laste check
if true, revert changed to false and return true
*/
bool Enigme::hasChanged()
{
	if (changed)
	{
		changed = false;
		return true;
	}
	return false;
}

/*
return the id of the door(s) controled by the enigme
*/
int Enigme::getDoor() const
{
	return doorId;
}

/*
set the resolved state and put changed at true if a change has been made
*/
void Enigme::setResolved(bool isResolved)
{
	if (resolved != isResolved)
	{
		changed = true;
	}
	resolved = isResolved;
}

void Enigme::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	//do nothing by default
}