#include "Rectangle.h"
#include "Application.h"

Rectangle::Rectangle(std::string name) : Polygon(name) {
	Application* app = Application::getInstance();
	std::cout << "Rectangle constructor\n";
}

Rectangle::Rectangle(std::string name, sf::Vector2f position, sf::Vector2f dimensions): Polygon(name) {
	this->setPosition(position);
	this->dimensions = dimensions;
	std::cout << "Rectangle constructor\n";
}

Rectangle::~Rectangle() {
	std::cout << "Rectangle destructor\n";
}

double Rectangle::getArea() const {
	return this->dimensions.x * this->dimensions.y;
}

double Rectangle::getPerimeter() const {
	return 2 * this->dimensions.x + 2 * this->dimensions.y;
}

void Rectangle::updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput) {
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
	std::string dimensionsText = dimensionsInput->textStream.str();
	sf::Vector2f dimensions;
	for (int i = 0; i < dimensionsText.length(); i++) {
		if (dimensionsText[i] == '\n') {
			continue;
		}
		else if (dimensionsText[i] == '(') {
			tempNumber = "";
		}
		else if (dimensionsText[i] == ')') {
			y = std::stoi(tempNumber);
			tempNumber = "";
			dimensions = { static_cast<float>(x), static_cast<float>(y) };
			x = 0;
			y = 0;
		}
		else if (dimensionsText[i] == ',') {
			x = std::stoi(tempNumber);
			tempNumber = "";
		}
		else if (dimensionsText[i] == ';') {
			tempNumber = "";
		}
		else {
			tempNumber += dimensionsText[i];
		}
	}
	Application* app = Application::getInstance();
	this->name = nameInput->textStream.str();
	this->setPosition(position);
	this->dimensions = dimensions;
	this->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(app->figuresList.size() - 1) * 50),
		sf::Color::Yellow, app->font, this->name + "\nArea:" + std::to_string(this->getArea())
		+ std::to_string(this->getArea()) + "\nPerimeter:" + std::to_string(this->getPerimeter()) };
	this->update();
}

std::size_t Rectangle::getPointCount() const {
	return 4;
}

sf::Vector2f Rectangle::getPoint(std::size_t index) const {
	switch (index) {
		default:
		case 0: return sf::Vector2f(0, 0);
		case 1: return sf::Vector2f(this->dimensions.x, 0);
		case 2: return sf::Vector2f(this->dimensions.x, -this->dimensions.y);
		case 3: return sf::Vector2f(0, -this->dimensions.y);
	}
}