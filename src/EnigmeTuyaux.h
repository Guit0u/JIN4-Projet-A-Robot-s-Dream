#pragma once
#include "SFML/Graphics.hpp"
#include "Enigme.h"
#include "Tuyau.h"
#include <string>
#include <vector>
#include <map>

class EnigmeTuyaux : public Enigme //puzzle where the player is supposed to link pipes by rotating them to create a closed circuit
								   //many variables and method are in frenglish and I'm truly sorry for that
{
public:
	explicit EnigmeTuyaux(int doorId);
	//add pipes from file
	void addTuyauFixe(std::string const& type,int orientation, std::pair<float,float> const& position);
	void addTuyauMobile(int id,std::string const& type, int orientation, std::pair<float,float> const& position, std::vector<int> const& switchs);

	//add pipes to the solution map
	void addTuyauSolution(int id, std::vector<int>const& solutions);

	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset) override;

	void updateCurrState(const Tuyau* tuyau); //update the current configuration when a pipe is rotated
	void inputEvent(int id, int value) override;
	void checkResolved(); //compare the current configuration with the solution
private:
	std::map<int,std::vector<int>> solution; //for each pipe in the solution, there's a vector of valid orientations. A straight pipe is horizontal wether it's 
											 //right up or upside down, so the matching vector will contain the orientations 0 and 2

	std::map<int, int> currState;//current pipes configuration
	std::map<int,std::vector<Tuyau*>> switchToTuyaux;//for each switch, gives the pipes they're linked to
	std::vector<std::unique_ptr<Tuyau>> tuyaux;//pipes of the puzzle
};