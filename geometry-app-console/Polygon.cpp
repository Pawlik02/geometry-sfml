#include "Polygon.h"

Polygon::Polygon(std::string name, Point verticies[]) {
	this->name = name;
	this->verticies = verticies;
}

Polygon::~Polygon() {
	std::cout << "Polygon destructor\n";
}