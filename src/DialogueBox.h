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

private :
	std::vector<std::unique_ptr<std::pair<std::pair<sf::Texture,sf::Sprite>,sf::Text>>> lines; //chaque ligne de texte est accompagnée d'une texture et d'un sprite du locuteur
	sf::RectangleShape background;
	sf::Font font; //il faut garder la police en vie (acab cependant)
	int currentLine = 0; //la ligne de dialogue qu'on est en train de lire
	bool dialogueRead = false; //on ne lit le dialogue qu'une fois par niveau meme si on resoud plusieurs fois l'énigme

};
