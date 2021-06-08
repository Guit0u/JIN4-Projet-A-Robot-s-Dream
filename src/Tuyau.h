#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class Tuyau
{
public:
	explicit Tuyau(std::string const& type, int orientation, std::pair<float, float> const& position);//constucteur pour tuyau fixe
	explicit Tuyau(int id,std::string const& type, int orientation, std::pair<float, float> const &position);//constructeur pour tuyau mobile
	void draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset);
	void rotate();
	int getId() const;
	int getOrientation() const;
private:
	enum class typeTuyau {
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