#pragma once
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include <string>
#include <vector>

class DialogueBox { //manages dialogues loading and displaying
public:
	explicit DialogueBox() = default;
	void load(pugi::xml_node const &node,sf::RenderWindow &window); //read dialogues from xml
	void display(sf::RenderWindow &window); 
	bool setNextLine(); 

private :
	std::vector<std::unique_ptr<std::pair<std::pair<sf::Texture,sf::Sprite>,sf::Text>>> lines; //each line comes with a asset of the speaker and their text
	sf::RectangleShape background;
	sf::Font font; //font must be kept alive
	int currentLine = 0; //the line to be displayed
	bool dialogueRead = false; //dialogue is displayed only once per level, even if puzzle is solved multiple times

};
