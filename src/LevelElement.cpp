#include "LevelElement.h"


LevelElement::LevelElement(std::string const& color) :
	color(color)
{
}


b2Body* LevelElement::getBodyPointer()
{
	return body;
}

void LevelElement::setBodyPointer(b2Body* ptr)
{
	body = ptr;
}


sf::Color getColorFromString(std::string const& s) {

	if (s.compare("Black") == 0)
		return sf::Color::Black;
	if (s.compare("Red") == 0)
		return sf::Color::Red;
	if (s.compare("Yellow") == 0)
		return sf::Color::Yellow;
	if (s.compare("Green") == 0)
		return sf::Color::Green;
	if (s.compare("Blue") == 0)
		return sf::Color::Blue;
	if (s.compare("White") == 0)
		return sf::Color::White;
	if (s.compare("Magenta") == 0)
		return sf::Color::Magenta;
	if (s.compare("Cyan") == 0)
		return sf::Color::Cyan;
	if (s.compare("Transparent") == 0)
		return sf::Color::Transparent;
	return sf::Color::Black;
}

void LevelElement::draw(sf::RenderWindow& window, std::pair<float, float> viewportOffset)
{
	b2Fixture* fixture = body->GetFixtureList();

	auto const poly = (b2PolygonShape*)fixture->GetShape();
	int32 vertexCount = poly->m_count;

	sf::ConvexShape convex;
	convex.setPointCount(vertexCount);

	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 pos = poly->m_vertices[i];
		pos += body->GetPosition();
		convex.setPoint(i, sf::Vector2f(pos.x, -pos.y));
	}
	convex.setPosition(sf::Vector2f(-viewportOffset.first, -viewportOffset.second));
	convex.setFillColor(getColorFromString(color));
	convex.setOutlineColor(sf::Color::White);
	convex.setOutlineThickness(0);
	window.draw(convex);
}

void LevelElement::interract() {
	printf("pas un levier\n");
}