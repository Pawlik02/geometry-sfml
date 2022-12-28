#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

class TextBox
{
	public:
		TextBox(sf::Vector2f size, sf::Vector2f position, int characterSize, sf::Color color, sf::Font& font);
		void textEntered(sf::Event event);
		void draw(sf::RenderWindow& window);
		std::string getTextStream();
		void clearText();

		
	private:
		std::ostringstream textStream;
		sf::Text textVisual;
		sf::RectangleShape boxVisual;
		void deleteLastChar();
};