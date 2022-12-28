#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"

class Polygon: public sf::Shape
{
	public:
		Polygon(std::string name, std::vector<sf::Vector2f> verticies);
		~Polygon();
		std::string name;
		std::vector<sf::Vector2f> verticies;

	private:
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
};
