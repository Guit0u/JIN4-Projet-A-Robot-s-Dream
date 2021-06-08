#pragma once
#include "LevelElement.h"

/*
class used to define static physic element (wall, ground)
*/
class StaticElement : public LevelElement
{
public:
	explicit StaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file);

};