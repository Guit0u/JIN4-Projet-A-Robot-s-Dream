#include "EnigmeTuyaux.h"

EnigmeTuyaux::EnigmeTuyaux(int doorId) : Enigme(doorId)
{}

void EnigmeTuyaux::addTuyauFixe(std::string const& type, int orientation, std::pair<float, float> const& position) { //immovable pipe doesn't need much treatment
	auto ptr = std::make_unique<Tuyau>(type,orientation,position);
	tuyaux.push_back(move(ptr));
}

void EnigmeTuyaux::addTuyauMobile(int id,std::string const& type, int orientation, std::pair<float, float> const& position, std::vector<int> const &switchs) {
	auto ptr = std::make_unique<Tuyau>(id,type, orientation, position);
	currState[id] = orientation;
	for (auto switchId : switchs) { // manage switches linked to this pipe
		if (switchToTuyaux.find(switchId) != switchToTuyaux.end()) {
			switchToTuyaux[switchId].push_back(ptr.get()); //if switch is linked to another pipe, pipe is added to the switch's vector
		}
		else {
			switchToTuyaux[switchId] = std::vector<Tuyau*>{ptr.get()}; //if not, switch's vector is initialized to this pipe
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
		for (size_t i = 0; i < switchToTuyaux[id].size(); i++) //rotates all pipes linked to this switch
		{
			switchToTuyaux[id][i]->rotate(); 
			updateCurrState(switchToTuyaux[id][i]);	
		}
	}
	checkResolved(); //check if we matched the solution
}

void EnigmeTuyaux::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) {
	for (size_t i = 0; i < tuyaux.size(); i++)
	{
		tuyaux.at(i)->draw(window,viewportOffset);
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