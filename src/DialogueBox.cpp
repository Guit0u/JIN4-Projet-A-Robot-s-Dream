#include "sfml/Graphics.hpp"
#include "box2d/box2d.h"
#include "pugixml.hpp"
#include <string>
#include "DialogueBox.h"
#include <iostream>

using namespace std;

sf::Color getColorFromString(string s) {

    if (s.compare("Black") == 0)
        return sf::Color::Black;
    if (s.compare("Red") == 0)
        return sf::Color::Red;
    if (s.compare("Yellow") == 0)
        return sf::Color::Yellow;
    if (s.compare("Green") == 0)
        return sf::Color::Green;
    if (s.compare("Blue") == 0)
        return sf::Color::Blue;
    if (s.compare("White") == 0)
        return sf::Color::White;
    if (s.compare("Magenta") == 0)
        return sf::Color::Magenta;
    if (s.compare("Cyan") == 0)
        return sf::Color::Cyan;
    if (s.compare("Transparent") == 0)
        return sf::Color::Transparent;
    return sf::Color::Black;
}


void DialogueBox::load(pugi::xml_node const &node, sf::RenderWindow &window) {
	line.setCharacterSize(node.attribute("CharacterSize").as_int());
    line.setFillColor(getColorFromString(node.attribute("TextColor").as_string()));	
    line.setString(node.attribute("string").as_string());
    line.setPosition(sf::Vector2f{ 10.f,window.getSize().y * 0.66f });


    background.setFillColor(getColorFromString(node.attribute("BackColor").as_string()));
    background.setOutlineColor(getColorFromString(node.attribute("BackOutlineColor").as_string()));
    background.setOutlineThickness(2);
    background.setPosition(sf::Vector2f{10.f,window.getSize().y * 0.66f });
    background.setSize(sf::Vector2f{window.getSize().x-20.f, window.getSize().y*0.33f-10.f});

    currNode = node;
}

void DialogueBox::display(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(line);
}

sf::Text DialogueBox::getText() {
    return line;
}

void DialogueBox::setFont(sf::Font const & font) {
    line.setFont(font);
}

void DialogueBox::setNextLine() {
    if (currNode.next_sibling()) {
        currNode = currNode.next_sibling();
        line.setCharacterSize(currNode.attribute("CharacterSize").as_int());
        line.setFillColor(getColorFromString(currNode.attribute("TextColor").as_string()));
        line.setString(currNode.attribute("string").as_string());
    }
   
}