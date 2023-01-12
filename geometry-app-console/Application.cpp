#include "Application.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Polygon.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "TextInput.h"
#include "Button.h"
#include "Exception.h"

Application* Application::instancePtr = NULL;

Application* Application::getInstance() {
	if (instancePtr == NULL) {
		instancePtr = new Application();
		return instancePtr;
	}
	else {
		return instancePtr;
	}
}

Application::Application() {
	std::cout << "Started application\n";
	this->selectedFigure = nullptr;
	this->font.loadFromFile("arial.ttf");
}

Application::~Application() {
	std::cout << "Closed application\n";
}

void Application::addFigure(Figure* figure) {
	this->figuresList.push_back(figure);
}

void Application::deleteFigure(std::string name) {
	if (name == "") {
		for (int i = 0; i < this->figuresList.size(); i++) {
			if (this->figuresList[i] == this->selectedFigure) {
				delete this->figuresList[i];
				this->figuresList.erase(this->figuresList.begin() + i);
				break;
			}
		}
	}
	else {
		for (int i = 0; i < this->figuresList.size(); i++) {
			if (this->figuresList[i]->name == name) {
				delete this->figuresList[i];
				this->figuresList.erase(this->figuresList.begin() + i);
				break;
			}
		}
	}
	this->reloadMenuButtons();
}

void Application::reloadMenuButtons() {
	for (int i = 0; i < this->figuresList.size(); i++) {
		this->figuresList[i]->menuButton.setPosition(sf::Vector2f(603, 178 + static_cast<float>(i) * 50));
	}
}

void Application::createPolygon(std::string nameInput, std::string verticiesInput, sf::Color color) {
	std::string tempNumber;
	std::vector<sf::Vector2f> verticies;
	int x = 0, y = 0;
	for (int i = 0; i < verticiesInput.length(); i++) {
		if (verticiesInput[i] == '\n') {
			continue;
		}
		else if (verticiesInput[i] == '(') {
			tempNumber = "";
		}
		else if (verticiesInput[i] == ')') {
			y = std::stoi(tempNumber);
			tempNumber = "";
			verticies.push_back(sf::Vector2f(static_cast<float>(x) + 300, static_cast<float>(-y) + 300));
			x = 0;
			y = 0;
		}
		else if (verticiesInput[i] == ',') {
			x = std::stoi(tempNumber);
			tempNumber = "";
		}
		else if (verticiesInput[i] == ';') {
			tempNumber = "";
		}
		else {
			tempNumber += verticiesInput[i];
		}
	}
	if (verticies.size() > 0) {
		Polygon* polygon = new Polygon(nameInput, verticies);
		polygon->setFillColor(color);
		polygon->setOutlineColor(color);
		polygon->setOutlineThickness(1);
		polygon->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 178 + static_cast<float>(this->figuresList.size()) * 50),
			sf::Color::Yellow, this->font, polygon->name + "\nArea:" + std::to_string(polygon->getArea()) + "\nPerimeter:" +
			std::to_string(polygon->getPerimeter()) };
		this->addFigure(polygon);
	}
}

void Application::createRectangle(std::string nameInput, std::string positionInput, std::string dimensionsInput, sf::Color color) {
	std::string positionText = positionInput;
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
	std::string dimensionsText = dimensionsInput;
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
	Rectangle* rectangle = new Rectangle(nameInput, position, dimensions);
	rectangle->setFillColor(color);
	rectangle->setOutlineColor(color);
	rectangle->setOutlineThickness(1);
	rectangle->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 178 + static_cast<float>(this->figuresList.size()) * 50),
		sf::Color::Yellow, this->font, rectangle->name + "\nArea:" + std::to_string(rectangle->getArea()) +"\nPerimeter:" +
		std::to_string(rectangle->getPerimeter()) };
	this->addFigure(rectangle);
}

void Application::createCircle(std::string nameInput, std::string positionInput, std::string radiusInput, sf::Color color) {
	std::string positionText = positionInput;
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
	Circle* circle = new Circle(nameInput, position, std::stoi(radiusInput));
	circle->setFillColor(color);
	circle->setOrigin(static_cast<float>(circle->getRadius()), static_cast<float>(circle->getRadius()));
	circle->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 178 + static_cast<float>(this->figuresList.size()) * 50),
		sf::Color::Yellow, this->font, circle->name + "\nArea:" + std::to_string(circle->getArea()) + "\nPerimeter:" +
		std::to_string(circle->getPerimeter()) };
	this->addFigure(circle);
}

void Application::createSquare(std::string nameInput, std::string positionInput, std::string widthInput, sf::Color color) {
	std::string positionText = positionInput;
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
	Square* square = new Square(nameInput, position, std::stoi(widthInput));
	square->setFillColor(color);
	square->setOutlineColor(color);
	square->setOutlineThickness(1);
	square->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 178 + static_cast<float>(this->figuresList.size()) * 50),
		sf::Color::Yellow, this->font, square->name + "\nArea:" + std::to_string(square->getArea()) + "\nPerimeter:" +
		std::to_string(square->getPerimeter()) };
	this->addFigure(square);
}

sf::Font Application::getFont() {
	return this->font;
}

void Application::saveToFile(TextInput* fileNameInput) {
	std::ofstream file;
	std::string className;
	file.open("pliki\\" + fileNameInput->textStream.str() + ".txt");
	for (int i = 0; i < this->figuresList.size(); i++) {
		className = typeid(*this->figuresList[i]).name();
		if (className == "class Polygon") {
			file << *this->figuresList[i];
		}
		if (className == "class Rectangle") {
			file << *this->figuresList[i];
		}
		if (className == "class Circle") {
			file << *this->figuresList[i];
		}
		if (className == "class Square") {
			file << *this->figuresList[i];
		}
	}
	file.close();
}

void Application::loadFromFile(TextInput* fileNameInput) {
	std::string name;
	std::string verticies;
	std::string position;
	std::string dimensions;
	std::string radius;
	std::string width;
	std::string colorText;
	std::string r;
	std::string g;
	std::string b;

	bool readValue = false;
	bool readColorValue = false;
	int i;

	std::ifstream file;
	std::string line;
	file.open("pliki\\" + fileNameInput->textStream.str() + ".txt");
	while (getline(file, line)) {
		if (line.substr(0, 26) == "{\"type\":\"Polygon\",\"name\":\"") {
			i = line.find("name") + 7;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					name += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("verticies") + 12;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					verticies += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("color") + 9;
			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					r += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					g += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					b += line[i];
				}
				i++;
			}
			readValue = false;

			this->createPolygon(name, verticies, sf::Color(std::stoi(r), std::stoi(g), std::stoi(b)));
		}
		if (line.substr(0, 28) == "{\"type\":\"Rectangle\",\"name\":\"") {
			i = line.find("name") + 7;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					name += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("position") + 11;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					position += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("dimensions") + 13;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					dimensions += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("color") + 9;
			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					r += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					g += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					b += line[i];
				}
				i++;
			}
			readValue = false;
			this->createRectangle(name, position, dimensions, sf::Color(std::stoi(r), std::stoi(g), std::stoi(b)));
		}

		if (line.substr(0, 25) == "{\"type\":\"Circle\",\"name\":\"") {
			i = line.find("name") + 7;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					name += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("position") + 11;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					position += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("radius") + 9;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					radius += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("color") + 9;
			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					r += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					g += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					b += line[i];
				}
				i++;
			}
			readValue = false;
			this->createCircle(name, position, radius, sf::Color(std::stoi(r), std::stoi(g), std::stoi(b)));
		}

		if (line.substr(0, 25) == "{\"type\":\"Square\",\"name\":\"") {
			i = line.find("name") + 7;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					name += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("position") + 11;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					position += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("width") + 8;
			while (!readValue) {
				if (line[i] == '"') {
					readValue = true;
				}
				else if (!readValue) {
					width += line[i];
				}
				i++;
			}
			readValue = false;

			i = line.find("color") + 9;
			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					r += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					g += line[i];
				}
				i++;
			}
			readValue = false;

			while (!readValue) {
				if (line[i] == ',' || line[i] == ')') {
					readValue = true;
				}
				else if (!readValue) {
					b += line[i];
				}
				i++;
			}
			readValue = false;
			this->createSquare(name, position, width, sf::Color(std::stoi(r), std::stoi(g), std::stoi(b)));
		}
		name = "";
		verticies = "";
		position = "";
		dimensions = "";
		radius = "";
		width = "";
		colorText = "";
		r = "";
		g = "";
		b = "";
	}
	file.close();
}

void Application::start() {
	sf::Event event;

	sf::RectangleShape menuBorder(sf::Vector2f(3, 800));
	sf::RectangleShape menuButtonsLine(sf::Vector2f(199, 3));
	sf::RectangleShape menuTextBoxLine(sf::Vector2f(600, 3));
	sf::RectangleShape xAxis(sf::Vector2f(600, 1));
	sf::RectangleShape yAxis(sf::Vector2f(1, 600));
	menuBorder.setFillColor(sf::Color::Black);
	menuBorder.setPosition(sf::Vector2f(600, 0));
	menuButtonsLine.setFillColor(sf::Color::Black);
	menuButtonsLine.setPosition(sf::Vector2f(600, 50));
	menuTextBoxLine.setFillColor(sf::Color::Black);
	menuTextBoxLine.setPosition(sf::Vector2f(0, 597));
	xAxis.setFillColor(sf::Color::Black);
	xAxis.setPosition(sf::Vector2f(0, 300));
	yAxis.setFillColor(sf::Color::Black);
	yAxis.setPosition(sf::Vector2f(300, 0));

	TextInput* input1 = new TextInput(sf::Vector2f(200, 200), sf::Vector2f(0, 600), 15, sf::Color::Black, this->font);
	TextInput* input2 = new TextInput(sf::Vector2f(200, 200), sf::Vector2f(200, 600), 15, sf::Color::Black, this->font);
	TextInput* input3 = new TextInput(sf::Vector2f(200, 200), sf::Vector2f(400, 600), 15, sf::Color::Black, this->font);
	TextInput* input4 = new TextInput(sf::Vector2f(197, 25), sf::Vector2f(603, 50), 15, sf::Color::Black, this->font);
	this->textInputList.push_back(input1);
	this->textInputList.push_back(input2);
	this->textInputList.push_back(input3);
	this->textInputList.push_back(input4);

	Button createFigureButton(sf::Vector2f(50, 25), sf::Vector2f(603, 0), sf::Color(119, 227, 57), this->font, "Create");
	Button deleteFigureButton(sf::Vector2f(50, 25), sf::Vector2f(653, 0), sf::Color(227, 11, 11), this->font, "Delete");
	Button updateFigureButton(sf::Vector2f(50, 25), sf::Vector2f(703, 0), sf::Color(245, 127, 10), this->font, "Update");
	
	Button* polygonButton = new Button(sf::Vector2f(50, 25), sf::Vector2f(603, 25), sf::Color(181, 201, 232), this->font, "Polygon");
	Button* rectangleButton = new Button(sf::Vector2f(65, 25), sf::Vector2f(653, 25), sf::Color(181, 201, 232), this->font, "Rectangle");
	Button* circleButton = new Button(sf::Vector2f(40, 25), sf::Vector2f(718, 25), sf::Color(181, 201, 232), this->font, "Circle");
	Button* squareButton = new Button(sf::Vector2f(50, 25), sf::Vector2f(758, 25), sf::Color(181, 201, 232), this->font, "Square");
	this->buttonList.push_back(polygonButton);
	this->buttonList.push_back(rectangleButton);
	this->buttonList.push_back(circleButton);
	this->buttonList.push_back(squareButton);

	Button saveFile(sf::Vector2f(100, 25), sf::Vector2f(603, 75), sf::Color(119, 227, 57), this->font, "Save to file");
	Button loadFile(sf::Vector2f(100, 25), sf::Vector2f(703, 75), sf::Color(119, 227, 57), this->font, "Load from file");

	Button* color1 = new Button(sf::Vector2f(60, 20), sf::Vector2f(606, 103), sf::Color(227, 52, 47), this->font);
	Button* color2 = new Button(sf::Vector2f(60, 20), sf::Vector2f(672, 103), sf::Color(246, 153, 63), this->font);
	Button* color3 = new Button(sf::Vector2f(60, 20), sf::Vector2f(738, 103), sf::Color(255, 237, 74), this->font);
	Button* color4 = new Button(sf::Vector2f(60, 20), sf::Vector2f(606, 129), sf::Color(56, 193, 114), this->font);
	Button* color5 = new Button(sf::Vector2f(60, 20), sf::Vector2f(672, 129), sf::Color(77, 192, 181), this->font);
	Button* color6 = new Button(sf::Vector2f(60, 20), sf::Vector2f(738, 129), sf::Color(52, 144, 220), this->font);
	Button* color7 = new Button(sf::Vector2f(60, 20), sf::Vector2f(606, 155), sf::Color(101, 116, 205), this->font);
	Button* color8 = new Button(sf::Vector2f(60, 20), sf::Vector2f(672, 155), sf::Color(149, 97, 226), this->font);
	Button* color9 = new Button(sf::Vector2f(60, 20), sf::Vector2f(738, 155), sf::Color(246, 109, 155), this->font);
	this->colorList.push_back(color1);
	this->colorList.push_back(color2);
	this->colorList.push_back(color3);
	this->colorList.push_back(color4);
	this->colorList.push_back(color5);
	this->colorList.push_back(color6);
	this->colorList.push_back(color7);
	this->colorList.push_back(color8);
	this->colorList.push_back(color9);

	while (this->window.isOpen()) {
		while (this->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window.close();
			}
			if (event.type == sf::Event::TextEntered) {
				if (this->selectedTextInput != nullptr) {
					this->selectedTextInput->textEntered(event);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.control && event.key.code == sf::Keyboard::V) {
					if (this->selectedTextInput != nullptr) {
						this->selectedTextInput->textPasted(event);
					}
				}
			}
			if (event.type == sf::Event::MouseMoved) {
				if (createFigureButton.isMouseOver(this->window)) {
					createFigureButton.setColor(sf::Color(85, 161, 42));
				}
				else {
					createFigureButton.setColor(sf::Color(119, 227, 57));
				}
				if (deleteFigureButton.isMouseOver(this->window)) {
					deleteFigureButton.setColor(sf::Color(179, 7, 7));
				}
				else {
					deleteFigureButton.setColor(sf::Color(227, 11, 11));
				}
				if (updateFigureButton.isMouseOver(this->window)) {
					updateFigureButton.setColor(sf::Color(207, 107, 8));
				}
				else {
					updateFigureButton.setColor(sf::Color(245, 127, 10));
				}
				if (saveFile.isMouseOver(this->window)) {
					saveFile.setColor(sf::Color(99, 189, 47));
				}
				else {
					saveFile.setColor(sf::Color(119, 227, 57));
				}
				if (loadFile.isMouseOver(this->window)) {
					loadFile.setColor(sf::Color(99, 189, 47));
				}
				else {
					loadFile.setColor(sf::Color(119, 227, 57));
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (createFigureButton.isMouseOver(this->window)) {
					try {
						if (this->selectedColor == nullptr) {
							throw Exception("Nie ma koloru!");
						}
						else if (this->selectedFigureType == polygonButton) {
							this->createPolygon(input1->textStream.str(), input2->textStream.str(), selectedColor->getColor());
						}
						else if (this->selectedFigureType == rectangleButton) {
							this->createRectangle(input1->textStream.str(), input2->textStream.str(), input3->textStream.str(), selectedColor->getColor());
						}
						else if (this->selectedFigureType == circleButton) {
							this->createCircle(input1->textStream.str(), input2->textStream.str(), input3->textStream.str(), selectedColor->getColor());
						}
						else if (this->selectedFigureType == squareButton) {
							this->createSquare(input1->textStream.str(), input2->textStream.str(), input3->textStream.str(), selectedColor->getColor());
						}
						if (this->selectedFigureType != nullptr) {
							this->selectedFigureType->setColor(sf::Color(181, 201, 232));
							this->selectedFigureType = nullptr;
						}
						for (int i = 0; i < this->textInputList.size(); i++) {
							this->textInputList[i]->clearText();
						}
					}
					catch (Exception exp) {
						std::cout << "Error: " << exp.getNumber() << ", message: " << exp.getMessage() << '\n';
					}
				}
				if (deleteFigureButton.isMouseOver(this->window)) {
					this->deleteFigure();
					for (int i = 0; i < this->textInputList.size(); i++) {
						this->textInputList[i]->clearText();
					}
				}
				if (updateFigureButton.isMouseOver(this->window)) {
					if (this->selectedFigure == nullptr || this->selectedColor == nullptr) {
						continue;
					}
					else if (this->selectedFigureType == polygonButton) {
						this->selectedFigure->updateFigure(input1, input2, selectedColor->getColor());
					}
					else if (this->selectedFigureType == rectangleButton) {
						this->selectedFigure->updateFigure(input1, input2, input3, selectedColor->getColor());
					}
					else if (this->selectedFigureType == circleButton) {
						this->selectedFigure->updateFigure(input1, input2, input3, selectedColor->getColor());
					}
					else if (this->selectedFigureType == squareButton) {
						this->selectedFigure->updateFigure(input1, input2, input3, selectedColor->getColor());
					}
					if (this->selectedFigureType != nullptr) {
						this->selectedFigureType->setColor(sf::Color(181, 201, 232));
						this->selectedFigureType = nullptr;
					}
					for (int i = 0; i < this->textInputList.size(); i++) {
						this->textInputList[i]->clearText();
					}
				}
				if (saveFile.isMouseOver(this->window)) {
					this->saveToFile(input4);
				}
				if (loadFile.isMouseOver(this->window)) {
					this->loadFromFile(input4);
				}
				// Figures list
				for (int i = 0; i < this->figuresList.size(); i++) {
					if (this->figuresList[i]->menuButton.isMouseOver(this->window)) {
						this->selectedFigure = this->figuresList[i];
						this->figuresList[i]->menuButton.setColor(sf::Color::Cyan);
						break;
					}
					this->selectedFigure = nullptr;
					this->figuresList[i]->menuButton.setColor(sf::Color::Yellow);
				}
				for (int i = 0; i < this->figuresList.size(); i++) {
					if (this->figuresList[i]->menuButton.isMouseOver(this->window) && this->selectedFigure != nullptr) {
						for (int i = 0; i < this->figuresList.size(); i++) {
							this->figuresList[i]->menuButton.setColor(sf::Color::Yellow);
						}
						this->selectedFigure = nullptr;
					}
					if (this->figuresList[i]->menuButton.isMouseOver(this->window)) {
						this->figuresList[i]->menuButton.setColor(sf::Color::Cyan);
						this->selectedFigure = this->figuresList[i];
					}
				}
				// Text inputs list
				for (int i = 0; i < this->textInputList.size(); i++) {
					if (this->textInputList[i]->isSelected(this->window)) {
						this->selectedTextInput = this->textInputList[i];
						break;
					}
					this->selectedTextInput = nullptr;
				}
				for (int i = 0; i < this->textInputList.size(); i++) {
					if (this->textInputList[i]->isSelected(this->window) && this->selectedTextInput != nullptr) {
						this->selectedTextInput = nullptr;
					}
					if (this->textInputList[i]->isSelected(this->window)) {
						this->selectedTextInput = this->textInputList[i];
					}
				}
				// Color list
				for (int i = 0; i < this->colorList.size(); i++) {
					if (this->colorList[i]->isMouseOver(this->window) && this->selectedColor) {
						for (int i = 0; i < this->colorList.size(); i++) {
							this->colorList[i]->buttonVisual.setOutlineColor(sf::Color::Black);
							this->colorList[i]->buttonVisual.setOutlineThickness(0);
						}
					}
					if (this->colorList[i]->isMouseOver(this->window)) {
						this->colorList[i]->buttonVisual.setOutlineColor(sf::Color::Black);
						this->colorList[i]->buttonVisual.setOutlineThickness(3);
						this->selectedColor = this->colorList[i];
					}
				}
				// Figure types list
				for (int i = 0; i < this->buttonList.size(); i++) {
					if (this->buttonList[i]->isMouseOver(this->window) && this->selectedFigureType) {
						for (int i = 0; i < this->buttonList.size(); i++) {
							this->buttonList[i]->setColor(sf::Color(181, 201, 232));
						}
					}
					if (this->buttonList[i]->isMouseOver(this->window)) {
						this->buttonList[i]->setColor(sf::Color(155, 173, 201));
						this->selectedFigureType = this->buttonList[i];
					}
				}
			}
		}
		
		this->window.clear(sf::Color::White);
		this->window.draw(menuBorder);
		this->window.draw(menuTextBoxLine);

		createFigureButton.draw(this->window);
		deleteFigureButton.draw(this->window);
		updateFigureButton.draw(this->window);

		if (this->selectedFigureType == polygonButton) {
			input1->draw(this->window);
			input2->draw(this->window);
		}
		else if (this->selectedFigureType == rectangleButton) {
			input1->draw(this->window);
			input2->draw(this->window);
			input3->draw(this->window);
		}
		else if (this->selectedFigureType == circleButton) {
			input1->draw(this->window);
			input2->draw(this->window);
			input3->draw(this->window);
		}
		else if (this->selectedFigureType == squareButton) {
			input1->draw(this->window);
			input2->draw(this->window);
			input3->draw(this->window);
		}
		input4->draw(this->window);
		polygonButton->draw(this->window);
		rectangleButton->draw(this->window);
		circleButton->draw(this->window);
		squareButton->draw(this->window);
		saveFile.draw(this->window);
		loadFile.draw(this->window);

		for (int i = 0; i < this->figuresList.size(); i++) {
			this->window.draw(*this->figuresList[i]);
			this->figuresList[i]->menuButton.draw(this->window);
		}

		for (int i = 0; i < this->colorList.size(); i++) {
			this->colorList[i]->draw(this->window);
		}
		this->window.draw(xAxis);
		this->window.draw(yAxis);
		this->window.display();
	}
}