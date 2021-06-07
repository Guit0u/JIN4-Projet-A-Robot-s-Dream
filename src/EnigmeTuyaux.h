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
	void addTuyauFixe(std::string const& type,int orientation, std::pair<float,float> const& position);
	void addTuyauMobile(int id,std::string const& type, int orientation, std::pair<float,float> const& position, std::vector<int> const& switchs);
	void addTuyauSolution(int id, std::vector<int>const& solutions);

	void draw(sf::RenderWindow& window) override;

	void updateCurrState(const Tuyau* tuyau);
	void inputEvent(int id, int value) override;
	void checkResolved();
private:
	std::map<int,std::vector<int>> solution;
	std::map<int, int> currState;
	std::map<int,std::vector<Tuyau*>> switchToTuyaux;
	std::vector<std::unique_ptr<Tuyau>> tuyaux;
};