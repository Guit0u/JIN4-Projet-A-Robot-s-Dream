#pragma once
#include "sfml/Graphics.hpp"
#include "box2d/box2d.h"
#include "pugixml.hpp"
#include <string>
class DialogueBox {
public:
	explicit DialogueBox() = default;
	void load(pugi::xml_node const &node,sf::RenderWindow &window);
	void display(sf::RenderWindow &window);
	sf::Text getText();
	void setFont(sf::Font const& font);
	void setNextLine();

private :
	sf::Text line;
	sf::RectangleShape background;
	pugi::xml_node currNode;
};
