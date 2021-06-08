#include "Tuyau.h"
#include <iostream>

void setOriginAndReajust(sf::Transformable& object, const sf::Vector2f& newOrigin) { //gere l'affichage
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
}

Tuyau::Tuyau(std::string const& typeTuyau, int orientation, std::pair<float, float> const& position) : orientation(orientation), position(position) {
	if (typeTuyau.compare("droit") == 0) {
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

Tuyau::Tuyau(int id,std::string const& typeTuyau, int orientation, std::pair<float, float> const& position) : id(id), orientation(orientation), position(position){
	
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
	sprite.setPosition(sf::Vector2f{position.first,position.second});
	setOriginAndReajust(sprite, sf::Vector2f{ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });

	for (int i = 0; i < orientation; i++)
		sprite.rotate(90);
}

int Tuyau::getId() const { return id; }
int Tuyau::getOrientation() const { return orientation; }

void Tuyau::rotate() {
	orientation++;
	orientation = orientation % 4;
	sprite.rotate(90.0f); //on change l'orientation et l'affichage
}

void Tuyau::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	sprite.setPosition(-viewportOffset.first,-viewportOffset.second);
	window.draw(sprite);
}