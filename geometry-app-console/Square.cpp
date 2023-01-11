#include "Square.h"
#include "Application.h"

Square::Square(std::string name, sf::Vector2f position, int width): Rectangle(name) {
	this->setPosition(position);
	this->width = width;
	std::cout << "Square constructor\n";
}

Square::~Square() {
	std::cout << "Square destructor\n";
}

double Square::getArea() const {
	return pow(this->width, 2);
}

double Square::getPerimeter() const {
	return abs(this->width * 4);
}

sf::Vector2f Square::getPoint(std::size_t index) const {
	switch (index) {
	default:
	case 0: return sf::Vector2f(0, 0);
	case 1: return sf::Vector2f(static_cast<float>(this->width), 0);
	case 2: return sf::Vector2f(static_cast<float>(this->width), static_cast<float>(-this->width));
	case 3: return sf::Vector2f(0, static_cast<float>(-this->width));
	}
}

void Square::updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* widthInput, sf::Color color) {
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
	this->setFillColor(color);
	this->setOutlineColor(color);
	this->width = std::stoi(widthInput->textStream.str());
	this->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 178 + static_cast<float>(app->figuresList.size() - 1) * 50),
		sf::Color::Yellow, app->font, this->name + "\nArea:" + std::to_string(this->getArea()) + "\nPerimeter:" +
		std::to_string(this->getPerimeter()) };
	this->update();
}

std::string Square::print() {
	std::string position;
	std::string dimensions;
	std::string color;
	position += "(";
	position += std::to_string(this->getPosition().x - 300);
	position += ", ";
	position += std::to_string(-this->getPosition().y + 300);
	position += ")";
	color = "(" + std::to_string(this->getFillColor().r) + ", " + std::to_string(this->getFillColor().g) + ", " + std::to_string(this->getFillColor().b) + ")";
	return "{\"type\":\"Square\",\"name\":\"" + this->name + "\",\"position\":\"" + position + "\",\"width\":\"" + std::to_string(this->width) + "\",\"color\":\"" + color + "\"}\n";
}