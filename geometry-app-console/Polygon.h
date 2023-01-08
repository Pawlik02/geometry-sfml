#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Button.h"
#include "TextInput.h"

class Polygon: public Figure
{
	public:
		Polygon(std::string name);
		Polygon(std::string name, std::vector<sf::Vector2f> verticies);
		~Polygon();
		void updateFigure(TextInput* nameInput, TextInput* verticiesInput);
		void updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput);
		double getArea() const;
		double getPerimeter() const;

	private:
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
};
