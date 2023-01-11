#pragma once
#include "Button.h"
#include <iostream>
#include "TextInput.h"

class Figure: public sf::Shape
{
	public:
		Figure(std::string name);
		std::string name;
		Button menuButton;
		std::vector<sf::Vector2f> verticies;
		virtual double getArea() const = 0;
		virtual double getPerimeter() const = 0;
		virtual void updateFigure(TextInput* nameInput, TextInput* verticiesInput, sf::Color color) = 0;
		virtual void updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput, sf::Color color) = 0;
		virtual std::string print() = 0;
		friend std::ostream& operator<<(std::ostream& out, Figure& figure);
};
std::ostream& operator<<(std::ostream& out, Figure& figure);