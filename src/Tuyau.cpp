#include "Tuyau.h"


Tuyau::Tuyau(std::string const& typeTuyau, int orientation, std::pair<int, int> const& position) : orientation(orientation), position(position){
	
	if(typeTuyau.compare("droit")==0){
		type = typeTuyau::droit;
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
	orientation = value;
}