#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class Tuyau // Class managing the pipes for the pipes puzzle (EnigmeTuyaux)
			//Yes i know this class should be called Pipe sorry again
{
public:
	explicit Tuyau(std::string const& type, int orientation, std::pair<float, float> const& position); //for immovable pipes
	explicit Tuyau(int id,std::string const& type, int orientation, std::pair<float, float> const &position);//for rotating pipes, which need ids
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);
	void rotate(); //change the orientation and rotate the sprite

	int getId() const;
	int getOrientation() const;
private:
	enum class typeTuyau { //different pipes types to get the right texture
		droit,
		te,
		coude,
		croix,
	};
	int id = -1;
	typeTuyau type = typeTuyau::droit;

	int orientation; 
	std::pair<float,float> position;
	sf::Texture texture;
	sf::Sprite sprite;
};