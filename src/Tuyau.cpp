#include "Tuyau.h"
#include <iostream>


//function which allows to set the origin right to rotate around the center of the sprite. Tried otherwise but eh, only this worked
void setOriginAndReajust(sf::Transformable& object, const sf::Vector2f& newOrigin) { 
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
}

Tuyau::Tuyau(std::string const& typeTuyau, int orientation, std::pair<float, float> const& pos) : orientation(orientation), position(pos) {
	//set up the right texture
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
		/*bool result = texture.loadFromFile("resources/tuyauCroix.png");
		if (!result) {
			std::cerr << "coudl not load file" << std::endl;
		} this file currently not exists
		*/
	}
	//set up sprite
	sprite.setTexture(texture);
	setOriginAndReajust(sprite,sf::Vector2f(texture.getSize().x/2, texture.getSize().y/2));

	for (int i = 0; i < orientation; i++)
		sprite.rotate(90);
}

Tuyau::Tuyau(int id,std::string const& typeTuyau, int orientation, std::pair<float, float> const& pos) : id(id), orientation(orientation), position(pos){
	
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
	setOriginAndReajust(sprite, sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));

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
	sprite.setPosition(position.first-viewportOffset.first,-position.second-viewportOffset.second);
	window.draw(sprite);
}