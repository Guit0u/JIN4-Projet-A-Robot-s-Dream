#include "Level.h"


void Level::load(b2World& world, pugi::xml_node node, sf::RenderWindow &window)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		world.DestroyBody(elements[i]->getBodyPointer());
	}
	elements.clear();

	auto levelNode = node.child("Level");

	for (auto child : levelNode.children())
	{
		if (strcmp("StaticElement", child.name()) == 0 )
		{
			addStaticElement(world,
				b2Vec2(child.attribute("posX").as_float(), child.attribute("posY").as_float()),
				b2Vec2(child.attribute("sizeX").as_float(), child.attribute("sizeY").as_float()),
				child.attribute("color").value());
		}
		else if (strcmp("DynamicElement", child.name()) == 0 )
		{
			addDynamicElement(world,
				b2Vec2(child.attribute("posX").as_float(), child.attribute("posY").as_float()),
				b2Vec2(child.attribute("sizeX").as_float(), child.attribute("sizeY").as_float()),
				child.attribute("density").as_float(), child.attribute("friction").as_float(),
				child.attribute("color").value());
		}
	}

	auto dialogueNode = node.child("dialogue");
	dialogue.load(dialogueNode, window);

}

void Level::setNextLine() {
	dialogue.setNextLine();
}

void Level::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(window, viewportOffset);
	}

	dialogue.display(window);
	
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

void Level::addPressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId)
{
	auto ptr = std::make_unique<PressurePlate>(world, pos, size, color, inputId);
	elements.push_back(move(ptr));
}





void Level::enigmeInput(int id, int value) const
{
	printf("input %d with value %d\n", id, value);
}