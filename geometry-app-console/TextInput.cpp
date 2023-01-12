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
