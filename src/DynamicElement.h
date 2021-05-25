#pragma once
#include "LevelElement.h"

class DynamicElement : public LevelElement
{
public:
	explicit DynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction);

};
