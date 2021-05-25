#pragma once
#include "sfml/Graphics.hpp"
#include "box2d/box2d.h"
#include "pugixml.hpp"
#include <string>
class DialogueBox {
public:
	explicit DialogueBox(pugi::xml_node const &node,sf::RenderWindow &window);
	void display(sf::RenderWindow &window);
	sf::Text getText();
	void setFont(sf::Font const& font);

private :
	sf::Text line;
	sf::RectangleShape background;
};
