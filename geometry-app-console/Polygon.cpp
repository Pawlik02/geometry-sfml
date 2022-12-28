#include "Polygon.h"

Polygon::Polygon(std::string name, std::vector<sf::Vector2f> verticies) {
	this->name = name;
	this->verticies = verticies;
}

Polygon::~Polygon() {
	std::cout << "Polygon destructor\n";
}

std::size_t Polygon::getPointCount() const {
	return this->verticies.size();
}

sf::Vector2f Polygon::getPoint(std::size_t index) const {
	return this->verticies[index];
}