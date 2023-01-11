#pragma once
#include "Rectangle.h"
class Square: public Rectangle
{
	public:
		Square(std::string name, sf::Vector2f position, int width);
		~Square();
		double getArea() const;
		double getPerimeter() const;
		void updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* widthInput, sf::Color color);
		int width;
		std::string print();
	private:
		sf::Vector2f getPoint(std::size_t index) const;
};

