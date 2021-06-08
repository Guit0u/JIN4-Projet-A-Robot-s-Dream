#include "Tuyau.h"
#include <iostream>

Tuyau::Tuyau(std::string const& typeTuyau, int orientation, std::pair<float, float> const& pos) : orientation(orientation), position(pos) {
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
	sprite.setOrigin(-pos.first+texture.getSize().x/2, pos.second+texture.getSize().y/2);

	//for (int i = 0; i < orientation; i++)
		//sprite.rotate(90);
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
	sprite.setOrigin(-pos.first, pos.second);

	//for (int i = 0; i < orientation; i++)
		//sprite.rotate(90);
}

int Tuyau::getId() const { return id; }
int Tuyau::getOrientation() const { return orientation; }

void Tuyau::rotate() {
	orientation++;
	orientation = orientation % 4;
	sprite.rotate(90.0f); //on change l'orientation et l'affichage
}

void Tuyau::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	sprite.setOrigin(sprite.getOrigin().x - viewportOffset.first, sprite.getOrigin().y-viewportOffset.second);
	window.draw(sprite);
}