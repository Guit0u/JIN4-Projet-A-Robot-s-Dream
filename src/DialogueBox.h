#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "pugixml.hpp"
#include <string>
#include <vector>

class DialogueBox {
public:
	explicit DialogueBox() = default;
	void load(pugi::xml_node const &node,sf::RenderWindow &window);
	void display(sf::RenderWindow &window);
	bool setNextLine();
	void resetDialogue();

private :
	std::vector<std::unique_ptr<std::pair<std::pair<sf::Texture,sf::Sprite>,sf::Text>>> lines;
	sf::RectangleShape background;
	sf::Font font;
	int currentLine = 0;
	bool dialogueRead = false;

};
