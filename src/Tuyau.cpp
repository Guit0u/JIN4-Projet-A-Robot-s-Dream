#include "Tuyau.h"
#include <iostream>

void setOriginAndReajust(sf::Transformable& object, const sf::Vector2f& newOrigin) {
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
}

Tuyau::Tuyau(std::string const& typeTuyau, int orientation, std::pair<float, float> const& position) : orientation(orientation), position(position){
	
	if(typeTuyau.compare("droit")==0){
		type = typeTuyau::droit;
		bool result = texture.loadFromFile("resources/tuyauDroit.png");
		if (!result) {
			std::cerr << "coudl not load file" << std::endl;
		}
	}
	else if (typeTuyau.compare("coude") == 0) {
		type = typeTuyau::coude;
		bool result = texture.loadFromFile("resources/tuyauCoude.png");
		if (!result) {
			std::cerr << "coudl not load file" << std::endl;
		}
	}
	else if (typeTuyau.compare("te") == 0) {
		type = typeTuyau::te;
		bool result = texture.loadFromFile("resources/tuyauTe.png");
		if (!result) {
			std::cerr << "coudl not load file" << std::endl;
		}
	}
	else if (typeTuyau.compare("croix") == 0) {
		type = typeTuyau::croix;
	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f{ position.first,position.second });
	setOriginAndReajust(sprite, sf::Vector2f{ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });

	for (int i = 0; i < orientation; i++)
		sprite.rotate(90);
}


void Tuyau::rotate(int value) {
	orientation = value;
	sprite.rotate(90.0f);
}

void Tuyau::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}