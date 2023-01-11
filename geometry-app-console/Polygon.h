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
		void updateFigure(TextInput* nameInput, TextInput* verticiesInput, sf::Color color);
		void updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput, sf::Color color);
		double getArea() const;
		double getPerimeter() const;
		std::string print();

	private:
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
};