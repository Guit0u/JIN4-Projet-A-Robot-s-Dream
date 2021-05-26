#include "Level.h"


void Level::load(b2World& world, pugi::xml_node node)
{
	elements.clear();

	for (auto child : node.children())
	{
		if (child.name() == "StaticElement")
		{
			addStaticElement(world,
				b2Vec2(node.attribute("posX").as_float(), node.attribute("poxY").as_float()),
				b2Vec2(node.attribute("sizeX").as_float(), node.attribute("sizeY").as_float()),
				node.attribute("color").value());
		}
		else if (child.name() == "DynamicElement")
		{
			addDynamicElement(world,
				b2Vec2(node.attribute("posX").as_float(), node.attribute("poxY").as_float()),
				b2Vec2(node.attribute("sizeX").as_float(), node.attribute("sizeY").as_float()), 
				node.attribute("density").as_float(), node.attribute("friction").as_float(),
				node.attribute("color").value());
		}
	}
}


void Level::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(window, viewportOffset);
	}
	
}

void Level::addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color)
{
	auto ptr = std::make_unique<StaticElement>(world, pos, size, color);
	elements.push_back(move(ptr));
}

void Level::addDynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& color)
{
	auto ptr = std::make_unique<DynamicElement>(world, pos, size, density, friction, color);
	elements.push_back(move(ptr));
}