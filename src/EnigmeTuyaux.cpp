#include "EnigmeTuyaux.h"

EnigmeTuyaux::EnigmeTuyaux(int doorId) : Enigme(doorId)
{}

void EnigmeTuyaux::addTuyauFixe(std::string const& type, int orientation, std::pair<float, float> const& position) {
	auto ptr = std::make_unique<Tuyau>(type,orientation,position);
	tuyaux.push_back(move(ptr));
}

void EnigmeTuyaux::addTuyauMobile(int id,std::string const& type, int orientation, std::pair<float, float> const& position, std::vector<int> const &switchs) {
	auto ptr = std::make_unique<Tuyau>(id,type, orientation, position);
	currState[id] = orientation;
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

void EnigmeTuyaux::addTuyauSolution(int id, std::vector<int>const& solutions) {
	solution[id] = solutions;
}


void EnigmeTuyaux::updateCurrState(const Tuyau* tuyau) {
	if(tuyau->getId()>0)
		currState[tuyau->getId()] = tuyau->getOrientation();
}

void EnigmeTuyaux::inputEvent(int id, int value){
	if (switchToTuyaux.find(id) != switchToTuyaux.end()) {
		for (size_t i = 0; i < switchToTuyaux[id].size(); i++)
		{
			switchToTuyaux[id][i]->rotate();
			updateCurrState(switchToTuyaux[id][i]);	
		}
	}
	checkResolved();
}

void EnigmeTuyaux::draw(sf::RenderWindow& window) {
	for (size_t i = 0; i < tuyaux.size(); i++)
	{
		tuyaux.at(i)->draw(window);
	}
}

void EnigmeTuyaux::checkResolved() {
	bool isResolved = true;
	for (int i = 1; i <= currState.size();i++) {
		if (std::find(solution.at(i).begin(), solution.at(i).end(), currState.at(i)) == solution.at(i).end()) {
			isResolved = false;
		}
	}
	setResolved(isResolved);
}