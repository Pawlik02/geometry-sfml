#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include <iostream>

class Circle: public Figure
{
public:
    Circle(std::string name, sf::Vector2f position, int radius, std::size_t pointCount = 30);
    ~Circle();
    int getRadius() const;
    double getArea() const;
    double getPerimeter() const;
    void updateFigure(TextInput* nameInput, TextInput* verticiesInput);
    void updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput);

private:
    void setRadius(int radius);
    void setPointCount(std::size_t count);
    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;
    int radius;
    std::size_t pointCount;
};