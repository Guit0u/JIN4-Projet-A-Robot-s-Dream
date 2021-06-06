#include "Tuyau.h"
#include <iostream>

void setOriginAndReajust(sf::Transformable& object, const sf::Vector2f& newOrigin) {
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
}

Tuyau::Tuyau(std::string const& typeTuyau, int orientation, std::pair<int, int> const& position) : orientation(orientation), position(position){
	
	if(typeTuyau.compare("droit")==0){
		type = typeTuyau::droit;
		bool result = texture.loadFromFile("resources/tuyauDroit.png");
		if (!result) {
			std::cerr << "coudl not load file" << std::endl;
		}
		sprite.setTexture(texture);
		setOriginAndReajust(sprite, sf::Vector2f{ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });
		
		for (int i = 0; i < orientation; i++)
			sprite.rotate(90);
	}
	else if (typeTuyau.compare("coude") == 0) {
		type = typeTuyau::coude;
	}
	else if (typeTuyau.compare("te") == 0) {
		type = typeTuyau::te;
	}
	else if (typeTuyau.compare("croix") == 0) {
		type = typeTuyau::croix;
	}
}


void Tuyau::rotate(int value) {
	printf("je toooouuuurne");
	orientation = value;
	sprite.rotate(90.0f);
}

void Tuyau::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}