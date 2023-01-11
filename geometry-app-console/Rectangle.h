#pragma once
#include "Polygon.h"
class Rectangle: public Polygon
{
	public:
		Rectangle(std::string name);
		Rectangle(std::string name, sf::Vector2f position, sf::Vector2f dimensions);
		~Rectangle();
		double getArea() const;
		double getPerimeter() const;
		void updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput, sf::Color color);
		std::string print();
		sf::Vector2f dimensions;

	private:
		std::size_t getPointCount() const;
		sf::Vector2f getPoint(std::size_t index) const;
};

