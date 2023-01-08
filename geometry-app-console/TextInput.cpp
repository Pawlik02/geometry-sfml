#include <iostream>
#include "TextInput.h"
#include "Polygon.h"
#include "Application.h"
#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define CTRL_V 22

TextInput::TextInput(sf::Vector2f size, sf::Vector2f position, int characterSize, sf::Color color, sf::Font& font) {
	this->boxVisual.setSize(size);
	this->boxVisual.setPosition(position);
	this->boxVisual.setFillColor(sf::Color(208, 208, 208));
	this->textVisual.setPosition(position + sf::Vector2f(5, 5));
	this->textVisual.setCharacterSize(characterSize);
	this->textVisual.setFillColor(color);
	this->textVisual.setFont(font);
	this->font = font;
}

void TextInput::textEntered(sf::Event event) {
	if (event.text.unicode == BACKSPACE_KEY) {
		if (this->textStream.str().length() == 0) {
			this->clearText();
		}
		else {
			this->deleteLastChar();
		}
	}
	else if (event.text.unicode == CTRL_V) {}
	else if (event.text.unicode == ENTER_KEY) {}
	else if (event.text.unicode == ESCAPE_KEY) {}
	else {
		this->textStream << static_cast<char>(event.text.unicode);
	}
	this->textVisual.setString(textStream.str());
}

void TextInput::textPasted(sf::Event event) {
	for (int i = 0; i < sf::Clipboard::getString().getSize(); i++) {
		this->textStream << static_cast<char>(sf::Clipboard::getString()[i]);
	}
}

void TextInput::draw(sf::RenderWindow& window) {
	window.draw(this->boxVisual);
	window.draw(this->textVisual);
}

void TextInput::deleteLastChar() {
	std::string oldText = this->textStream.str();
	std::string newText;
	for (int i = 0; i < oldText.length() - 1; i++) {
		newText += oldText[i];
	}
	this->clearText();
	this->textStream << newText;
}

void TextInput::clearText() {
	this->textStream.str("");
	this->textVisual.setString(textStream.str());
}

bool TextInput::isSelected(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;
	if (mouseX > this->boxVisual.getPosition().x && mouseX < this->boxVisual.getPosition().x +
		this->boxVisual.getLocalBounds().width && mouseY > this->boxVisual.getPosition().y &&
		mouseY < this->boxVisual.getPosition().y + this->boxVisual.getLocalBounds().height) {
		return true;
	}
	return false;
}

//void Terminal::handleCommand(sf::Event event) {
//	Application* app = Application::getInstance();
//	std::string command = this->textStream.str();
//	std::string name;
//	int x = 0, y = 0;
//	bool readName = false;
//	std::string tempNumber;
//
//	if (command.substr(0, 13) == "createPolygon") {
//		std::vector<sf::Vector2f> verticies;
//
//		if (command[13] != ' ' || command[14] != '"') {
//			std::cout << "There will be an exception here!\n";
//		}
//
//		for (int i = 15; i < command.length(); i++) {
//			if (command[i] == '"') {
//				readName = true;
//			}
//			else if (!readName) {
//				name += command[i];
//			}
//			else if (command[i] == '\n') {
//				continue;
//			}
//			else if (command[i] == '(') {
//				tempNumber = "";
//			}
//			else if (command[i] == ')') {
//				y = std::stoi(tempNumber);
//				tempNumber = "";
//				verticies.push_back(sf::Vector2f(static_cast<float>(x + 300), static_cast<float>(-y + 300)));
//				x = 0;
//				y = 0;
//			}
//			else if (command[i] == ',') {
//				x = std::stoi(tempNumber);
//				tempNumber = "";
//			}
//			else if (command[i] == ';') {
//				tempNumber = "";
//			}
//			else {
//				tempNumber += command[i];
//			}
//		}
//		app->createPolygon(name, verticies);
//	}
//	if (command.substr(0, 15) == "createRectangle") {
//		std::vector<sf::Vector2f> verticies;
//
//		if (command[15] != ' ' || command[16] != '"') {
//			std::cout << "There will be an exception here!\n";
//		}
//
//		for (int i = 17; i < command.length(); i++) {
//			if (command[i] == '"') {
//				readName = true;
//			}
//			else if (!readName) {
//				name += command[i];
//			}
//			else if (command[i] == '\n') {
//				continue;
//			}
//			else if (command[i] == '(') {
//				tempNumber = "";
//			}
//			else if (command[i] == ')') {
//				y = std::stoi(tempNumber);
//				tempNumber = "";
//				verticies.push_back(sf::Vector2f(static_cast<float>(x + 300), static_cast<float>(-y + 300)));
//				x = 0;
//				y = 0;
//			}
//			else if (command[i] == ',') {
//				x = std::stoi(tempNumber);
//				tempNumber = "";
//			}
//			else if (command[i] == ';') {
//				tempNumber = "";
//			}
//			else {
//				tempNumber += command[i];
//			}
//		}
//		std::cout << name;
//		//app->createRectangle(name, position, width, height);
//	}
//	if (command.substr(0, 12) == "createCircle") {
//		int radius;
//		sf::Vector2f position;
//
//		if (command[12] != ' ' || command[13] != '"') {
//			std::cout << "There will be an exception here!\n";
//		}
//
//		for (int i = 14; i < command.length(); i++) {
//			if (command[i] == '"') {
//				readName = true;
//			}
//			else if (!readName) {
//				name += command[i];
//			}
//			else if (command[i] == '\n') {
//				continue;
//			}
//			else if (command[i] == '(') {
//				tempNumber = "";
//			}
//			else if (command[i] == ')') {
//				y = std::stoi(tempNumber);
//				tempNumber = "";
//				position = { static_cast<float>(x + 300), static_cast<float>(-y + 300) };
//			}
//			else if (command[i] == ',') {
//				x = std::stoi(tempNumber);
//				tempNumber = "";
//			}
//			else if (command[i] == ';') {
//				tempNumber = "";
//			}
//			else {
//				tempNumber += command[i];
//			}
//		}
//		radius = std::stoi(tempNumber);
//		app->createCircle(name, position, radius);
//	}
//	if (command.substr(0, 6) == "delete") {
//		app->deleteFigure(command.substr(7));
//	}
//}
