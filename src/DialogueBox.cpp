#include "sfml/Graphics.hpp"
#include "box2d/box2d.h"
#include "pugixml.hpp"
#include <string>
#include "DialogueBox.h"
#include <iostream>

using namespace std;

sf::Color getColorFromString(string s) { //return sf::Color for text and background displaying

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

    lines.clear(); //clear the lines to load new ones

    currentLine = 0; //the first line to be read

    auto currNode = node.first_child();

    if (!font.loadFromFile(node.attribute("FontFile").as_string())){
        cout << "Could not open font file" << endl;
            exit(1);
    }

    while(currNode) {

        //background settings

        background.setFillColor(getColorFromString(node.attribute("BackColor").as_string()));
        background.setOutlineColor(getColorFromString(node.attribute("BackOutlineColor").as_string()));
        background.setOutlineThickness(3);
        background.setPosition(sf::Vector2f{ 3.f,window.getSize().y * 0.70f-1.f });
        background.setSize(sf::Vector2f{ window.getSize().x - 6.f, window.getSize().y * 0.30f});

        //text and picture settings
        auto p = make_unique<std::pair<std::pair<sf::Texture,sf::Sprite>,sf::Text>>();
        bool result = p->first.first.loadFromFile(currNode.attribute("Speaker").as_string());
        if (!result)
        {
            std::cerr << "Could not open file image" << std::endl;
            return;
        }

        //set image
        p->first.second.setTexture(p->first.first);
        p->first.second.setPosition(background.getPosition());

        //set text
        p->second.setCharacterSize(currNode.attribute("CharacterSize").as_int());
        p->second.setFillColor(getColorFromString(currNode.attribute("TextColor").as_string()));
        p->second.setString(currNode.attribute("string").as_string());  
        p->second.setPosition(sf::Vector2f{ background.getPosition().x + p->first.first.getSize().x + 30 , background.getPosition().y + background.getSize().y/3 });
        p->second.setFont(font);

        lines.push_back(move(p));


        currNode = currNode.next_sibling();
    }
}

void DialogueBox::display(sf::RenderWindow& window) {
 
        window.draw(background);
        window.draw(lines.at(currentLine).get()->first.second);
        window.draw(lines.at(currentLine).get()->second);
  
}

bool DialogueBox::setNextLine() { // allows the player to read the next line, and quit dialogue after last node with text
    if (currentLine < lines.size() - 2) {
        currentLine++;
        return false;
    }                                   
    if (currentLine < lines.size() - 1)
        currentLine++;
    return true;    
}