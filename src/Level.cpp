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
		else if (strcmp("Door", child.name()) == 0)
		{
			addDoor(world,
				b2Vec2(child.attribute("posX").as_float(), child.attribute("posY").as_float()),
				b2Vec2(child.attribute("sizeX").as_float(), child.attribute("sizeY").as_float()),
				child.attribute("color").value(), child.attribute("id").as_int());
		}
		else if (strcmp("PressurePlate", child.name()) == 0)
		{
			addPressurePlate(world,
				b2Vec2(child.attribute("posX").as_float(), child.attribute("posY").as_float()),
				b2Vec2(child.attribute("sizeX").as_float(), child.attribute("sizeY").as_float()),
				child.attribute("color").value(), child.attribute("id").as_int());
		}
		else if (strcmp("Switch", child.name()) == 0)
		{
			addSwitch(world,
				b2Vec2(child.attribute("posX").as_float(), child.attribute("posY").as_float()),
				b2Vec2(child.attribute("sizeX").as_float(), child.attribute("sizeY").as_float()),
				child.attribute("color").value(), child.attribute("id").as_int(),
				child.attribute("nbStates").as_int());
		}
	}

	auto enigmeNode = node.child("Enigme");
	for (auto child : enigmeNode.children())
	{
		printf("load new enigme\n");
		if (strcmp("EnigmeLink", child.name()) == 0)
		{
			printf("load new enigmeLink\n");
			addEnigmeLink(child.attribute("inputId").as_int(),
				child.attribute("condValue").as_int(),
				child.attribute("outputId").as_int());
		}
	}

	auto dialogueNode = node.child("dialogue");
	dialogue.load(dialogueNode, window);

}

bool Level::setNextLine() {
	return dialogue.setNextLine();
}

void Level::resetDialogue() {
	dialogue.resetDialogue();
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

void Level::addSwitch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId, int nbState) {
	auto ptr = std::make_unique<Switch>(world, pos, size, color, inputId, nbState);
	elements.push_back(move(ptr));
}

void Level::addDoor(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int id)
{
	auto ptr = std::make_unique<Door>(world, pos, size, color, id);
	elements.push_back(move(ptr));
}

void Level::addEnigmeLink(int inputId, int condValue, int outputId)
{
	auto ptr = std::make_unique<EnigmeLink>(inputId, condValue, outputId);
	enigmes.push_back(move(ptr));
}

void Level::enigmeInput(int id, int value) const
{
	for (int i = 0; i < enigmes.size(); i++)
	{
		enigmes[i]->inputEvent(id, value);
	}
}

void Level::checkSwitchs() {
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->interract())
		{
			auto ptr = dynamic_cast<Switch*>(elements[i].get());
			enigmeInput(ptr->getInputId(), ptr->getStateValue());
		}
	}
}

void Level::openDoor(int id, int state) {
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->setElementState(id, state);
	}
}

bool Level::checkEnigme()
{
	for (int i = 0; i < enigmes.size(); i++)
	{
		if (enigmes[i]->hasChanged())
		{
			openDoor(enigmes[i]->getDoor(), enigmes[i]->isResolved());
		}
	}
	
	if (enigmes.empty() || enigmes[enigmes.size() - 1]->isResolved())
	{
		return true;
	}
	return false;
}