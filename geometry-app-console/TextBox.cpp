#include "TextBox.h"
#include <iostream>
#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

TextBox::TextBox(sf::Vector2f size, sf::Vector2f position, int characterSize, sf::Color color, sf::Font& font) {
	this->boxVisual.setSize(size);
	this->boxVisual.setPosition(position);
	this->boxVisual.setFillColor(sf::Color(208, 208, 208));
	this->textVisual.setPosition(position + sf::Vector2f(5, 5));
	this->textVisual.setCharacterSize(characterSize);
	this->textVisual.setFillColor(color);
	this->textVisual.setFont(font);
}

void TextBox::textEntered(sf::Event event) {
	if (event.text.unicode == BACKSPACE_KEY) {
		if (this->textStream.str().length() == 0) {
			this->clearText();
		}
		else {
			this->deleteLastChar();
		}
	}
	else if (event.text.unicode == ENTER_KEY) {
		this->textStream << '\n';
	}
	else if (event.text.unicode == ESCAPE_KEY) {}
	else {
		if (this->textStream.str().length() % 100 == 0) {
			this->textStream << '\n';
		}
		this->textStream << static_cast<char>(event.text.unicode);
	}
	this->textVisual.setString(textStream.str());
}

void TextBox::draw(sf::RenderWindow& window) {
	window.draw(this->boxVisual);
	window.draw(this->textVisual);
}

void TextBox::deleteLastChar() {
	std::string oldText = this->textStream.str();
	std::string newText;
	for (int i = 0; i < oldText.length() - 1; i++) {
		newText += oldText[i];
	}
	this->clearText();
	this->textStream << newText;
}

std::string TextBox::getTextStream() {
	return this->textStream.str();
}

void TextBox::clearText() {
	this->textStream.str("");
	this->textVisual.setString(textStream.str());
}