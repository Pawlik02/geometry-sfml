#include "Circle.h"
#include "Application.h"
#include <SFML/Graphics.hpp>
#include <cmath>

const double pi = 3.14159265358979323846;

Circle::Circle(std::string name, sf::Vector2f position, int radius, std::size_t pointCount): 
    Figure(name),
    radius(radius),
    pointCount(pointCount)
{   
    this->setPosition(position);
    update();
    std::cout << "Cricle constructor\n";
}

Circle::~Circle() {
    std::cout << "Circle destructor\n";
}

void Circle::setRadius(int radius) {
    this->radius = radius;
    update();
}

int Circle::getRadius() const {
    return this->radius;
}

void Circle::setPointCount(std::size_t count) {
    this->pointCount = count;
    update();
}

std::size_t Circle::getPointCount() const {
    return this->pointCount;
}

sf::Vector2f Circle::getPoint(std::size_t index) const {
    float angle = index * 2 * pi / this->pointCount - pi / 2;
    float x = std::cos(angle) * this->radius;
    float y = std::sin(angle) * this->radius;

    return sf::Vector2f(this->radius + x, this->radius + y);
}

double Circle::getArea() const {
    return pi * pow(this->radius, 2);
}

double Circle::getPerimeter() const {
	return 2 * pi * this->radius;
}

void Circle::updateFigure(TextInput* nameInput, TextInput* verticiesInput) {
    std::cout << "MOCKUP";
}

void Circle::updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput) {
	std::string positionText = positionInput->textStream.str();
	sf::Vector2f position;
	std::string tempNumber;
	int x = 0, y = 0;
	for (int i = 0; i < positionText.length(); i++) {
		if (positionText[i] == '\n') {
			continue;
		}
		else if (positionText[i] == '(') {
			tempNumber = "";
		}
		else if (positionText[i] == ')') {
			y = std::stoi(tempNumber);
			tempNumber = "";
			position = { static_cast<float>(x) + 300, static_cast<float>(-y) + 300 };
			x = 0;
			y = 0;
		}
		else if (positionText[i] == ',') {
			x = std::stoi(tempNumber);
			tempNumber = "";
		}
		else if (positionText[i] == ';') {
			tempNumber = "";
		}
		else {
			tempNumber += positionText[i];
		}
	}
	Application* app = Application::getInstance();
	this->name = nameInput->textStream.str();
	this->setPosition(position);
	this->radius = std::stoi(dimensionsInput->textStream.str());
	this->setOrigin(static_cast<float>(this->getRadius()), static_cast<float>(this->getRadius()));
	this->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(app->figuresList.size() - 1) * 50),
		sf::Color::Yellow, app->font, this->name + "\nArea:" + std::to_string(this->getArea())
		+ std::to_string(this->getArea()) + "\nPerimeter:" +std::to_string(this->getPerimeter()) };
	this->update();
}