#include "Application.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Polygon.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "TextInput.h"
#include "Button.h"
#include <string>

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
		this->figuresList[i]->menuButton.setPosition(sf::Vector2f(603, 53 + static_cast<float>(i) * 50));
	}
}

void Application::createPolygon(TextInput* nameInput, TextInput* verticiesInput) {
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
		Polygon* polygon = new Polygon(nameInput->textStream.str(), verticies);
		polygon->setFillColor(sf::Color::Red);
		polygon->setFillColor(sf::Color::Red);
		polygon->setOutlineThickness(1);
		polygon->setOutlineColor(sf::Color::Red);
		polygon->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(this->figuresList.size()) * 50),
			sf::Color::Yellow, this->font, polygon->name + "\nArea:" + std::to_string(polygon->getArea()) + "\nPerimeter:" +
			std::to_string(polygon->getPerimeter()) };
		this->addFigure(polygon);
	}
}

void Application::createRectangle(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput) {
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
	Rectangle* rectangle = new Rectangle(nameInput->textStream.str(), position, dimensions);
	rectangle->setFillColor(sf::Color::Red);
	rectangle->setFillColor(sf::Color::Red);
	rectangle->setOutlineThickness(1);
	rectangle->setOutlineColor(sf::Color::Red);
	rectangle->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(this->figuresList.size()) * 50),
		sf::Color::Yellow, this->font, rectangle->name + "\nArea:" + std::to_string(rectangle->getArea())
		+ std::to_string(rectangle->getArea()) + "\nPerimeter:" + std::to_string(rectangle->getPerimeter()) };
	this->addFigure(rectangle);
}

void Application::createCircle(TextInput* nameInput, TextInput* positionInput, TextInput* radiusInput) {
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
	Circle* circle = new Circle(nameInput->textStream.str(), position, std::stoi(radiusInput->textStream.str()));
	circle->setFillColor(sf::Color::Red);
	circle->setOrigin(static_cast<float>(circle->getRadius()), static_cast<float>(circle->getRadius()));
	circle->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(this->figuresList.size()) * 50),
		sf::Color::Yellow, this->font, circle->name + "\nArea:" + std::to_string(circle->getArea()) +
		std::to_string(circle->getArea()) + "\nPerimeter:" + std::to_string(circle->getPerimeter()) };
	this->addFigure(circle);
}

void Application::createSquare(TextInput* nameInput, TextInput* positionInput, TextInput* widthInput) {
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
	Square* square = new Square(nameInput->textStream.str(), position, std::stoi(widthInput->textStream.str()));
	square->setFillColor(sf::Color::Red);
	square->setFillColor(sf::Color::Red);
	square->setOutlineThickness(1);
	square->setOutlineColor(sf::Color::Red);
	square->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 53 + static_cast<float>(this->figuresList.size()) * 50),
		sf::Color::Yellow, this->font, square->name + "\nArea:" + std::to_string(square->getArea())
		+ std::to_string(square->getArea()) + "\nPerimeter:" + std::to_string(square->getPerimeter()) };
	this->addFigure(square);
}

sf::Font Application::getFont() {
	return this->font;
}

void Application::start() {
	sf::Event event;

	sf::RectangleShape menuBorder(sf::Vector2f(3, 600));
	sf::RectangleShape menuButtonsLine(sf::Vector2f(199, 3));
	sf::RectangleShape menuTextBoxLine(sf::Vector2f(800, 3));
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
	this->textInputList.push_back(input1);
	this->textInputList.push_back(input2);
	this->textInputList.push_back(input3);

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
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (createFigureButton.isMouseOver(this->window)) {
					if (this->selectedFigureType == polygonButton) {
						this->createPolygon(input1, input2);
					}
					else if (this->selectedFigureType == rectangleButton) {
						this->createRectangle(input1, input2, input3);
					}
					else if (this->selectedFigureType == circleButton) {
						this->createCircle(input1, input2, input3);
					}
					else if (this->selectedFigureType == squareButton) {
						this->createSquare(input1, input2, input3);
					}
					if (this->selectedFigureType != nullptr) {
						this->selectedFigureType->setColor(sf::Color(181, 201, 232));
						this->selectedFigureType = nullptr;
					}
					for (int i = 0; i < this->textInputList.size(); i++) {
						this->textInputList[i]->clearText();
					}
				}
				if (deleteFigureButton.isMouseOver(this->window)) {
					this->deleteFigure();
					for (int i = 0; i < this->textInputList.size(); i++) {
						this->textInputList[i]->clearText();
					}
				}
				if (updateFigureButton.isMouseOver(this->window)) {
					if (this->selectedFigure == nullptr) {
						continue;
					}
					else if (this->selectedFigureType == polygonButton) {
						this->selectedFigure->updateFigure(input1, input2);
					}
					else if (this->selectedFigureType == rectangleButton) {
						this->selectedFigure->updateFigure(input1, input2, input3);
					}
					else if (this->selectedFigureType == circleButton) {
						this->selectedFigure->updateFigure(input1, input2, input3);
					}
					else if (this->selectedFigureType == squareButton) {
						this->selectedFigure->updateFigure(input1, input2, input3);
					}
					if (this->selectedFigureType != nullptr) {
						this->selectedFigureType->setColor(sf::Color(181, 201, 232));
						this->selectedFigureType = nullptr;
					}
					for (int i = 0; i < this->textInputList.size(); i++) {
						this->textInputList[i]->clearText();
					}
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
		this->window.draw(menuButtonsLine);
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
		polygonButton->draw(this->window);
		rectangleButton->draw(this->window);
		circleButton->draw(this->window);
		squareButton->draw(this->window);

		for (int i = 0; i < this->figuresList.size(); i++) {
			this->window.draw(*this->figuresList[i]);
			this->figuresList[i]->menuButton.draw(this->window);
		}

		this->window.draw(xAxis);
		this->window.draw(yAxis);
		this->window.display();
	}
}