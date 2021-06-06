#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class Tuyau
{
public:
	explicit Tuyau(std::string const& type, int orientation, std::pair<float, float> const &position);
	void draw(sf::RenderWindow& window);
	void rotate(int value);
private:
	enum class typeTuyau {
		droit,
		te,
		coude,
		croix,
	};
	typeTuyau type;
	int orientation;
	std::pair<float,float> position;
	sf::Texture texture;
	sf::Sprite sprite;
};