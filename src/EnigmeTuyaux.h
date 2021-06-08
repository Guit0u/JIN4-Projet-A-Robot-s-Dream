#pragma once
#include "SFML/Graphics.hpp"
#include "Enigme.h"
#include "Tuyau.h"
#include <string>
#include <vector>
#include <map>

class EnigmeTuyaux : public Enigme
{
public:
	explicit EnigmeTuyaux(int doorId);
	//ajouter des tuyaux depuis le xml
	void addTuyauFixe(std::string const& type,int orientation, std::pair<int,int> const& position);
	void addTuyauMobile(int id,std::string const& type, int orientation, std::pair<int, int> const& position, std::vector<int> const& switchs);
	void addTuyauSolution(int id, std::vector<int>const& solutions);

	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) override;

	void updateCurrState(const Tuyau* tuyau); //change quand on modifie l'orientation d'un tuyau
	void inputEvent(int id, int value) override;
	void checkResolved(); //compare l'état courant et la solution après un changement
private:
	std::map<int,std::vector<int>> solution; //on stocke la solution sous la forme d'un map d'un id de tuyau et d'un vecteur de solutions pour chaque tuyau
											 //par exemple un tuyau droit fonctionne dans 2 sens donc la solution doit contenir pour ce tuyau les etats 0 et 2 

	std::map<int, int> currState;//l'état courant de l'orientation des tuyaux mobiles
	std::map<int,std::vector<Tuyau*>> switchToTuyaux;//map qui link les interrupteurs et les tuyaux sur lesquels ils jouent
	std::vector<std::unique_ptr<Tuyau>> tuyaux;//la liste des tuyaux
};