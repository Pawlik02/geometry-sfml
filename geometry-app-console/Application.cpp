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

void Application::addFigure(Figure* figure) {
	this->figuresList.push_back(figure);
}

void Application::deleteFigure() {
	for (int i = 0; i < this->figuresList.size(); i++) {
		if (this->figuresList[i] == this->selectedFigure) {
			delete this->figuresList[i];
			this->figuresList.erase(this->figuresList.begin() + i);
			break;
		}
	}
	this->reloadMenuButtons();
}

void Application::reloadMenuButtons() {
	for (int i = 0; i < this->figuresList.size(); i++) {
		this->figuresList[i]->menuButton.setPosition(sf::Vector2f(603, 28 + static_cast<float>(i) * 50));
	}
}

void Application::createPolygon(sf::Event event, TextBox& textBox, sf::Font& font) {
	std::string textToParse = textBox.getTextStream();
	std::string tempNumber;
	std::vector<sf::Vector2f> verticies;
	int x=0, y=0;
	bool readName = false;
	std::string name;
	for (int i = 0; i < textToParse.length(); i++) {
		if (textToParse[i] == ':') {
			readName = true;
		}
		else if (!readName) {
			name += textToParse[i];
		}
		else if (textToParse[i] == '\n') {
			continue;
		}
		else if (textToParse[i] == '(') {
			tempNumber = "";
		}
		else if (textToParse[i] == ')') {
			y = std::stoi(tempNumber);
			tempNumber = "";
			verticies.push_back(sf::Vector2f(static_cast<float>(x) + 300, static_cast<float>(y) + 300));
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
		Polygon* polygon = new Polygon(name, verticies);
		polygon->setFillColor(sf::Color::Red);
		polygon->setFillColor(sf::Color::Red);
		polygon->setOutlineThickness(1);
		polygon->setOutlineColor(sf::Color::Red);
		polygon->menuButton = { sf::Vector2f(199, 50), sf::Vector2f(603, 28 + static_cast<float>(this->figuresList.size()) * 50),
			sf::Color::Yellow, font, polygon->name};
		this->addFigure(polygon);
	}
}

void Application::start() {
	sf::Event event;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::RectangleShape menuBorder(sf::Vector2f(3, 600));
	sf::RectangleShape menuButtonsLine(sf::Vector2f(199, 3));
	sf::RectangleShape menuTextBoxLine(sf::Vector2f(800, 3));
	sf::RectangleShape xAxis(sf::Vector2f(600, 1));
	sf::RectangleShape yAxis(sf::Vector2f(1, 600));
	menuBorder.setFillColor(sf::Color::Black);
	menuBorder.setPosition(sf::Vector2f(600, 0));
	menuButtonsLine.setFillColor(sf::Color::Black);
	menuButtonsLine.setPosition(sf::Vector2f(600, 25));
	menuTextBoxLine.setFillColor(sf::Color::Black);
	menuTextBoxLine.setPosition(sf::Vector2f(0, 597));
	xAxis.setFillColor(sf::Color::Black);
	xAxis.setPosition(sf::Vector2f(0, 300));
	yAxis.setFillColor(sf::Color::Black);
	yAxis.setPosition(sf::Vector2f(300, 0));

	TextBox textbox1(sf::Vector2f(800, 200), sf::Vector2f(0, 600), 15, sf::Color::Black, font);
	Button addFigureButton(sf::Vector2f(50, 25), sf::Vector2f(603, 0), sf::Color(67, 240, 10), font, "Add");
	Button deleteFigureButton(sf::Vector2f(50, 25), sf::Vector2f(653, 0), sf::Color(227, 11, 11), font, "Delete");

	while (this->window.isOpen()) {
		while (this->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window.close();
			}
			if (event.type == sf::Event::TextEntered) {
				textbox1.textEntered(event);
			}
			if (event.type == sf::Event::MouseMoved) {
				if (addFigureButton.isMouseOver(this->window)) {
					addFigureButton.setColor(sf::Color(52, 179, 11));
				}
				else {
					addFigureButton.setColor(sf::Color(67, 240, 10));
				}
				if (deleteFigureButton.isMouseOver(this->window)) {
					deleteFigureButton.setColor(sf::Color(179, 7, 7));
				}
				else {
					deleteFigureButton.setColor(sf::Color(227, 11, 11));
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (addFigureButton.isMouseOver(this->window)) {
					this->createPolygon(event, textbox1, font);
					textbox1.clearText();
				}
				if (deleteFigureButton.isMouseOver(this->window)) {
					this->deleteFigure();
					textbox1.clearText();
				}
				for (int i = 0; i < this->figuresList.size(); i++) {
					if (this->figuresList[i]->menuButton.isMouseOver(this->window) && this->isFigureSelected) {
						for (int i = 0; i < this->figuresList.size(); i++) {
							this->figuresList[i]->menuButton.setColor(sf::Color::Yellow);
						}
						this->isFigureSelected = false;
					}
					if (this->figuresList[i]->menuButton.isMouseOver(this->window)) {
						this->figuresList[i]->menuButton.setColor(sf::Color::Cyan);
						this->isFigureSelected = true;
						this->selectedFigure = this->figuresList[i];
					}
				}
			}
		}
		this->window.clear(sf::Color::White);
		this->window.draw(menuBorder);
		this->window.draw(menuButtonsLine);
		this->window.draw(menuTextBoxLine);

		textbox1.draw(this->window);
		addFigureButton.draw(this->window);
		deleteFigureButton.draw(this->window);

		for (int i = 0; i < this->figuresList.size(); i++) {
			this->window.draw(*this->figuresList[i]);
			this->figuresList[i]->menuButton.draw(this->window);
		}

		this->window.draw(xAxis);
		this->window.draw(yAxis);

		this->window.display();
	}
}