#include "Enigme.h"

Enigme::Enigme(int doorId) :
	doorId(doorId)
{}

bool Enigme::isResolved() const
{
	return resolved;
}

bool Enigme::hasChanged()
{
	if (changed)
	{
		changed = false;
		return true;
	}
	return false;
}

int Enigme::getDoor() const
{
	return doorId;
}

void Enigme::setResolved(bool isResolved)
{
	if (resolved != isResolved)
	{
		changed = true;
	}
	resolved = isResolved;
}