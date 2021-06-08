#pragma once
#include "box2d/box2d.h"
#include "Level.h"
#include "ContactElement.h"
#include <iostream>

/*
Class that generate the events call for the ContactElement class
*/
class ContactListener : public b2ContactListener
{
public:
	explicit ContactListener(Level const& level);

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

private:
	Level const* level;
};