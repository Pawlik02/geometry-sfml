#include "Polygon.h"
#include "Application.h"
#include "Button.h"

Polygon::Polygon(std::string name): Figure(name) {
	Application* app = Application::getInstance();
	std::cout << "Polygon constructor\n";
}

Polygon::Polygon(std::string name, std::vector<sf::Vector2f> verticies): Figure(name) {
	Application* app = Application::getInstance();
	this->verticies = verticies;
	std::cout << "Polygon constructor\n";
}

Polygon::~Polygon() {
	std::cout << "Polygon destructor\n";
}

std::size_t Polygon::getPointCount() const {
	return this->verticies.size();
}

sf::Vector2f Polygon::getPoint(std::size_t index) const {
	return this->verticies[index];
}

double Polygon::getArea() const{
	double leftSum = 0.0;
	double rightSum = 0.0;

	for (int i = 0; i < this->verticies.size(); ++i) {
		int j = (i + 1) % this->verticies.size();
		leftSum += this->verticies[i].x * this->verticies[j].y;
		rightSum += this->verticies[j].x * this->verticies[i].y;
	}

	return 0.5 * abs(leftSum - rightSum);
}

double Polygon::getPerimeter() const {
	float perimeter = 0;
	sf::Vector2f a, b;

	for (size_t i = 0; i < this->verticies.size(); ++i)
	{
		a = this->verticies[i];
		b = this->verticies[(i + 1) % this->verticies.size()];
		float segmentLength = std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
		perimeter += segmentLength;
	}
	return perimeter;
}

void Polygon::updateFigure(TextInput* nameInput, TextInput* verticiesInput) {
	std::string verticiesText = verticiesInput->textStream.str();
	std::string tempNumber;
	std::vector<sf::Vector2f> verticies;
	int x = 0, y = 0;
	for (int i = 0; i < verticiesText.length(); i++) {
		if (verticiesText[i] == '\n') {
			continue;
		}
		else if (verticiesText[i] == '(') {
			tempNumber = "";
		}
		else if (verticiesText[i] == ')') {
			y = std::stoi(tempNumber);
			tempNumber = "";
			verticies.push_back(sf::Vector2f(static_cast<float>(x) + 300, static_cast<float>(-y) + 300));
			x = 0;
			y = 0;
		}
		else if (verticiesText[i] == ',') {
			x = std::stoi(tempNumber);
			tempNumber = "";
		}
		else if (verticiesText[i] == ';') {
			tempNumber = "";
		}
		else {
			tempNumber += verticiesText[i];
		}
	}
	if (verticies.size() > 0) {
		Application* app = Application::getInstance();
		this->name = nameInput->textStream.str();
		this->verticies = verticies;
		this->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(app->figuresList.size() - 1) * 50),
			sf::Color::Yellow, app->font, this->name + "\nArea:" + std::to_string(this->getArea())
		+ std::to_string(this->getArea()) + "\nPerimeter:" + std::to_string(this->getPerimeter()) };
		this->update();
	}
}

void Polygon::updateFigure(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput) {
	std::cout << "MOCKUP";
}