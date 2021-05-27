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

    lines.clear();
    currentLine = 0;

    auto currNode = node.first_child();

    if (!font.loadFromFile(node.attribute("FontFile").as_string())){
        cout << "assassin de la police" << endl;
            exit(1);
    }

    while(currNode) {
        auto p = make_unique<sf::Text>();
        p->setCharacterSize(currNode.attribute("CharacterSize").as_int());
        p->setFillColor(getColorFromString(currNode.attribute("TextColor").as_string()));
        p->setString(currNode.attribute("string").as_string());
        p->setPosition(sf::Vector2f{ 10.f,window.getSize().y * 0.66f });
        p->setFont(font);
        lines.push_back(move(p));
        currNode = currNode.next_sibling();
    }

    background.setFillColor(getColorFromString(node.attribute("BackColor").as_string()));
    background.setOutlineColor(getColorFromString(node.attribute("BackOutlineColor").as_string()));
    background.setOutlineThickness(2);
    background.setPosition(sf::Vector2f{10.f,window.getSize().y * 0.66f });
    background.setSize(sf::Vector2f{window.getSize().x-20.f, window.getSize().y*0.33f-10.f});

}

void DialogueBox::display(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(*lines.at(currentLine).get());
}

sf::Text* DialogueBox::getText() {
    return lines.at(currentLine).get();
}

void DialogueBox::setNextLine() {
    if(currentLine<lines.size()-1)
        currentLine++;
}