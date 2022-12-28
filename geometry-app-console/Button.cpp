#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color color) {
	this->buttonVisual.setSize(size);
	this->buttonVisual.setPosition(position);
	this->buttonVisual.setFillColor(color);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(this->buttonVisual);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;
	if (mouseX > this->buttonVisual.getPosition().x && mouseX < this->buttonVisual.getPosition().x + this->buttonVisual.getLocalBounds().width &&
		mouseY > this->buttonVisual.getPosition().y && mouseY < this->buttonVisual.getPosition().y + this->buttonVisual.getLocalBounds().height) {
		return true;
	}
	return false;
}