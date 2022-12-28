#include "Application.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Polygon.h"
#include "TextBox.h"
#include "Button.h"
#include <string>

Application::Application() {
	std::cout << "Started application\n";
}

Application::~Application() {
	std::cout << "Closed application\n";
}

template<typename shapeType>
void Application::addShape(shapeType shape) {
	this->shapesList.push_back(shape);
}

void Application::createPolygon(sf::Event event, TextBox& textBox) {
	std::string textToParse = textBox.getTextStream();
	std::string tempNumber;
	std::vector<sf::Vector2f> verticies;
	int x=0, y=0;
	for (int i = 0; i < textToParse.length(); i++) {
		if (textToParse[i] == '(') {
			tempNumber = "";
		}
		else if (textToParse[i] == ')') {
			y = std::stoi(tempNumber);
			tempNumber = "";
			verticies.push_back(sf::Vector2f(x, y));
			x = 0;
			y = 0;
		}
		else if (textToParse[i] == ',') {
			x = std::stoi(tempNumber);
			tempNumber = "";
		}
		else if (textToParse[i] == ';') {
			tempNumber = "";
		}
		else {
			tempNumber += textToParse[i];
		}
	}
	if (verticies.size() > 0) {
		Polygon polygon("name", verticies);
		polygon.setFillColor(sf::Color::Red);
		polygon.setFillColor(sf::Color::Red);
		polygon.setOutlineThickness(1);
		polygon.setOutlineColor(sf::Color::Red);
		this->addShape<Polygon>(polygon);
	}
}

void Application::start() {
	sf::Event event;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::RectangleShape menuBorder(sf::Vector2f(199, 598));
	menuBorder.setOutlineColor(sf::Color::Black);
	menuBorder.setOutlineThickness(1);
	menuBorder.setPosition(sf::Vector2f(800, 1));

	TextBox textbox1(sf::Vector2f(199, 199), sf::Vector2f(800, 400), 15, sf::Color::Black, font);
	Button button1(sf::Vector2f(25, 25), sf::Vector2f(800, 1), sf::Color::Green);

	while (this->window.isOpen()) {
		while (this->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window.close();
			}
			if (event.type == sf::Event::TextEntered) {
				textbox1.textEntered(event);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (button1.isMouseOver(this->window)) {
					this->createPolygon(event, textbox1);
					textbox1.clearText();
				}
			}
		}
		this->window.clear(sf::Color::White);
		this->window.draw(menuBorder);

		textbox1.draw(this->window);
		button1.draw(this->window);

		for (int i = 0; i < this->shapesList.size(); i++) {
			this->window.draw(this->shapesList[i]);
		}

		this->window.display();
	}
}