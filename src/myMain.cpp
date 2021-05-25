#include "myMain.h"
#include "iostream"
#include "fstream"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include "DialogueBox.h"

using namespace std;

int myMain()
{
    //window
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML works!");
    window.setFramerateLimit(60);

    pugi::xml_document doc;
    doc.load_file("resources/test_dialogue.xml");
    pugi::xml_node currNode(doc.first_child().first_child());
    DialogueBox dialogue(doc.first_child().first_child(), window);

    sf::Font font;
    if (!font.loadFromFile(doc.first_child().attribute("FontFile").as_string())) {
        cout << "assassin de la police" << endl;
        exit(1);
    }
    dialogue.setFont(font);

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                dialogue.setNextLine(currNode);
            }
        }

        dialogue.display(window);
        
        
        window.display();
    }
    return  0;
}