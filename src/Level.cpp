#include "Level.h"


/*
Load the level from an xml node contening the data
the world parameter is the object doing the physique, needed to create physic objects
the window parameter is for the size of the DialogueBox
*/
void Level::load(b2World& world, pugi::xml_node node, sf::RenderWindow &window)
{
	// clear the level in order to load a new one (or reload it)
	for (size_t i = 0; i < elements.size(); i++)
	{
		world.DestroyBody(elements[i]->getBodyPointer());
	}
	elements.clear();
	enigmes.clear();

	// load the level

	auto levelNode = node.child("Level");
	if (levelNode)	// creates the elements of the level. Those correspond to the interactive parts of the level (ground included)
	{
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
					child.attribute("file").value());
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
					child.attribute("file").value(), child.attribute("id").as_int());
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
	}

	auto enigmeNode = node.child("Enigme");
	if (enigmeNode) // creates the enigmes of the level
	{
		for (auto child : enigmeNode.children())
		{
			if (strcmp("EnigmeLink", child.name()) == 0)
			{
				addEnigmeLink(child.attribute("inputId").as_int(),
					child.attribute("condValue").as_int(),
					child.attribute("outputId").as_int());
			}
			else if (strcmp("EnigmeTuyaux", child.name()) == 0) {
				addEnigmeTuyaux(child.attribute("output").as_int(), child);
			}
		}
	}

	auto dialogueNode = node.child("dialogue");
	if(dialogueNode) // load dialogue
		dialogue.load(dialogueNode, window);

}

/*
Set the next line of dilogue.
*/
bool Level::setNextLine() {
	return dialogue.setNextLine();
}

/*
Draw the divers componant of the level
the offset is used to put 0 0 at the center of the screen 
*/
void Level::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	for (size_t i = 0; i < elements.size(); i++) // draw the interactive part of the level
	{
		elements[i]->draw(window, viewportOffset);
	}

	for (size_t i = 0; i < enigmes.size(); i++) // draw the enigmes that need to be drawn
	{
		enigmes[i]->draw(window,viewportOffset);
	}


	dialogue.display(window); // draw the dialogue box
	
}


/* 
Call StaticElement constructor and put a unique_ptr to the object in elements
*/
void Level::addStaticElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file)
{
	auto ptr = std::make_unique<StaticElement>(world, pos, size, file);
	elements.push_back(move(ptr));
}

/*
Call DynamicElement constructor and put a unique_ptr to the object in elements
*/
void Level::addDynamicElement(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, float density, float friction, std::string const& color)
{
	auto ptr = std::make_unique<DynamicElement>(world, pos, size, density, friction, color);
	elements.push_back(move(ptr));
}

/*
Call PressurePlate constructor and put a unique_ptr to the object in elements
*/
void Level::addPressurePlate(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& color, int inputId)
{
	auto ptr = std::make_unique<PressurePlate>(world, pos, size, color, inputId);
	elements.push_back(move(ptr));
}

/*
Call Switch constructor and put a unique_ptr to the object in elements
*/
void Level::addSwitch(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int inputId, int nbState) {
	auto ptr = std::make_unique<Switch>(world, pos, size, file, inputId, nbState);
	elements.push_back(move(ptr));
}

/*
Call Door constructor and put a unique_ptr to the object in elements
*/
void Level::addDoor(b2World& world, b2Vec2 const& pos, b2Vec2 const& size, std::string const& file, int id)
{
	auto ptr = std::make_unique<Door>(world, pos, size, file, id);
	elements.push_back(move(ptr));
}

/*
Call EnigmeLink constructor and put a unique_ptr to the object in enigmes
*/
void Level::addEnigmeLink(int inputId, int condValue, int outputId)
{
	auto ptr = std::make_unique<EnigmeLink>(inputId, condValue, outputId);
	enigmes.push_back(move(ptr));
}

/*
Call EnigmeTuyaux constructor
add the tuyau composing the enigme
put a unique_ptr to the object in enigmes
*/
void Level::addEnigmeTuyaux(int outputId,pugi::xml_node node) {
	auto ptr = std::make_unique<EnigmeTuyaux>(outputId);
	for (auto child : node.children())
	{
		if (strcmp("TuyauFixe", child.name()) == 0)
		{
			ptr->addTuyauFixe(child.attribute("type").as_string(),
				child.attribute("orientation").as_int(),
				std::pair<float, float>{child.attribute("posX").as_float(),child.attribute("posY").as_float()});
		}
		else if (strcmp("TuyauMobile", child.name()) == 0) {
			std::vector<int> switchs;
			for(auto childSwitch : child.children()){
				switchs.push_back(childSwitch.attribute("id").as_int());
			}
			ptr->addTuyauMobile(child.attribute("id").as_int(),child.attribute("type").as_string(),
				child.attribute("orientation").as_int(),
				std::pair<float, float>{child.attribute("posX").as_float(), child.attribute("posY").as_float()},
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

/*
Methode called to input a value to a enigme
the id correspond to the id of an input port of the enigme
enigmes that do not posses a matching input id will ignore it
*/
void Level::enigmeInput(int id, int value) const
{
	for (int i = 0; i < enigmes.size(); i++)
	{
		enigmes[i]->inputEvent(id, value);
	}
}

/*
methode called when switch activation key is pressed
check if the element can be interacted with and input give an enigme input if true
*/
void Level::activateSwitchs() {
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->interract())
		{
			auto ptr = dynamic_cast<Switch*>(elements[i].get());
			enigmeInput(ptr->getInputId(), ptr->getStateValue());
		}
	}
}

/*
set a door object with a matching id to state ( 0 = close, 1+ = open)
LevelElement that are not door will juste do nothing 
*/
void Level::openDoor(int id, int state) {
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->setElementState(id, state);
	}
}

/*
check the states of the enigmes and affect the door 
return true if the last enigme is resolved (ie the level is completed)
*/
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




//methodes de tests

int Level::getNbElements() const
{
	return elements.size();
}

int Level::getNbEnigmes() const
{
	return enigmes.size();
}

LevelElement* Level::getElement(int i) const
{
	if (i < elements.size())
		return elements[i].get();
	return nullptr;
}

Enigme* Level::getEnigme(int i) const
{
	if(i < enigmes.size())
		return enigmes[i].get();
	return nullptr;
}