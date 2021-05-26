#pragma once
#include "LevelElement.h"

class StaticElement : public LevelElement
{
public:
	explicit StaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color);

};