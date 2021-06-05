#include "EnigmeTuyaux.h"

EnigmeTuyaux::EnigmeTuyaux(int doorId) : Enigme(doorId)
{}

void EnigmeTuyaux::addTuyauFixe(std::string const& type, int orientation, std::pair<int, int> const& position) {
	auto ptr = std::make_unique<Tuyau>(type,orientation,position);
	tuyaux.push_back(move(ptr));
}

void EnigmeTuyaux::addTuyauMobile(std::string const& type, int orientation, std::pair<int, int> const& position, std::vector<int> const &switchs) {
	auto ptr = std::make_unique<Tuyau>(type, orientation, position);
	
	for (auto switchId : switchs) {
		if (switchToTuyaux.find(switchId) != switchToTuyaux.end()) {
			switchToTuyaux[switchId].push_back(ptr.get());
		}
		else {
			switchToTuyaux[switchId] = std::vector<Tuyau*>{ptr.get()};
		}
	}
	tuyaux.push_back(move(ptr));
}

void EnigmeTuyaux::inputEvent(int id, int value){
	if (switchToTuyaux.find(id) != switchToTuyaux.end()) {
		for (size_t i = 0; i < switchToTuyaux[id].size(); i++)
		{
			switchToTuyaux[id][i]->rotate(value);
		}
	}
}

void EnigmeTuyaux::draw(sf::RenderWindow& window) {
	//do nothing
}