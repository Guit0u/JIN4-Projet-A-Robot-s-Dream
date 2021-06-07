#include "Level.h"



void Level::load(b2World& world, pugi::xml_node node, sf::RenderWindow &window)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		world.DestroyBody(elements[i]->getBodyPointer());
	}
	elements.clear();
	enigmes.clear();

	auto levelNode = node.child("Level");

	for (auto child : levelNode.children())
	{
		if (strcmp("StaticElement", child.name()) == 0 )
		{
			addStaticElement(world,
				b2Vec2(child.attribute("posX").as_float(), child.attribute("posY").as_float()),
				b2Vec2(child.attribute("sizeX").as_float(), child.attribute("sizeY").as_float()),
				child.attribute("file").as_string());
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
				child.attribute("file").as_string(), child.attribute("id").as_int());
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
				child.attribute("file").as_string(), child.attribute("id").as_int(),
				child.attribute("nbStates").as_int());
		}
	}

	auto enigmeNode = node.child("Enigme");
	for (auto child : enigmeNode.children())
	{
		if (strcmp("EnigmeLink", child.name()) == 0)
		{
			addEnigmeLink(child.attribute("inputId").as_int(),
				child.attribute("condValue").as_int(),
				child.attribute("outputId").as_int());
		}
		else if (strcmp("EnigmeTuyaux", child.name()) == 0){
			addEnigmeTuyaux(child.attribute("output").as_int(),child);
		}
	}

	auto dialogueNode = node.child("dialogue");
	dialogue.load(dialogueNode, window);

}

bool Level::setNextLine() {
	return dialogue.setNextLine();
}

void Level::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(window, viewportOffset);
	}

	for (size_t i = 0; i < enigmes.size(); i++)
	{
		enigmes[i]->draw(window);
	}


	dialogue.display(window);
	
}

void Level::addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file)
{
	auto ptr = std::make_unique<StaticElement>(world, pos, size, file);
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

void Level::addSwitch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId, int nbState) {
	auto ptr = std::make_unique<Switch>(world, pos, size, file, inputId, nbState);
	elements.push_back(move(ptr));
}

void Level::addDoor(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int id)
{
	auto ptr = std::make_unique<Door>(world, pos, size, file, id);
	elements.push_back(move(ptr));
}

void Level::addEnigmeLink(int inputId, int condValue, int outputId)
{
	auto ptr = std::make_unique<EnigmeLink>(inputId, condValue, outputId);
	enigmes.push_back(move(ptr));
}

void Level::addEnigmeTuyaux(int outputId,pugi::xml_node node) {
	auto ptr = std::make_unique<EnigmeTuyaux>(outputId);
	for (auto child : node.children())
	{
		if (strcmp("TuyauFixe", child.name()) == 0)
		{
			ptr->addTuyauFixe(child.attribute("type").as_string(),
				child.attribute("orientation").as_int(),
				std::pair<int, int>{child.attribute("posX").as_float(),child.attribute("posY").as_float()});
		}
		else if (strcmp("TuyauMobile", child.name()) == 0) {
			std::vector<int> switchs;
			for(auto childSwitch : child.children()){
				switchs.push_back(childSwitch.attribute("id").as_int());
			}
			ptr->addTuyauMobile(child.attribute("id").as_int(),child.attribute("type").as_string(),
				child.attribute("orientation").as_int(),
				std::pair<int, int>{child.attribute("posX").as_float(), child.attribute("posY").as_float()},
				switchs);
		}
		else if (strcmp("Solution", child.name()) == 0) {
			for (auto tuyauNode : child.children()) {
				std::vector<int> solutions;
				for (auto solNode : tuyauNode.children()) {
					solutions.push_back(solNode.attribute("orientation").as_int());
				}
				ptr->addTuyauSolution(tuyauNode.attribute("id").as_int(),solutions);
			}
		}
	}
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