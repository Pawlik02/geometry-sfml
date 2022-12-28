#include "Button.h"
#include <iostream>

Button::Button() {}

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Font& font, std::string text, int characterSize) {
	this->buttonVisual.setSize(size);
	this->buttonVisual.setPosition(position);
	this->buttonVisual.setFillColor(color);
	this->textVisual.setPosition(position + sf::Vector2f(5, 5));
	this->textVisual.setCharacterSize(characterSize);
	this->textVisual.setFillColor(sf::Color::Black);
	this->textVisual.setFont(font);
	this->textVisual.setString(text);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(this->buttonVisual);
	window.draw(this->textVisual);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;
	if (mouseX > this->buttonVisual.getPosition().x && mouseX < this->buttonVisual.getPosition().x +
		this->buttonVisual.getLocalBounds().width && mouseY > this->buttonVisual.getPosition().y &&
		mouseY < this->buttonVisual.getPosition().y + this->buttonVisual.getLocalBounds().height) {
		return true;
	}
	return false;
}

void Button::setColor(sf::Color color) {
	this->buttonVisual.setFillColor(color);
}

void Button::setPosition(sf::Vector2f position) {
	this->buttonVisual.setPosition(position);
	this->textVisual.setPosition(position + sf::Vector2f(5, 5));
}