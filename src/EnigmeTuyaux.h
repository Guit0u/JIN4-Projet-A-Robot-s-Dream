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
	void addTuyauFixe(std::string const& type,int orientation, std::pair<int,int> const& position);
	void addTuyauMobile(std::string const& type, int orientation, std::pair<int, int> const& position, std::vector<int> const& switchs);

	void draw(sf::RenderWindow& window) override;
	void inputEvent(int id, int value) override;
private:
	std::map<int,std::vector<int>> solution;
	std::map<int, int> currState;
	std::map<int,std::vector<Tuyau*>> switchToTuyaux;
	std::vector<std::unique_ptr<Tuyau>> tuyaux;
};