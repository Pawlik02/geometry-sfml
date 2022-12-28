#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Figure.h"

class Polygon: public Figure
{
	public:
		Polygon(std::string name, std::vector<sf::Vector2f> verticies);
		~Polygon();
		std::vector<sf::Vector2f> verticies;

	private:
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
};
