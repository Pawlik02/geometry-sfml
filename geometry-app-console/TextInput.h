#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

class TextInput
{
	public:
		TextInput(sf::Vector2f size, sf::Vector2f position, int characterSize, sf::Color color, sf::Font& font);
		void textEntered(sf::Event event);
		void textPasted(sf::Event event);
		void draw(sf::RenderWindow& window);
		void clearText();
		bool isSelected(sf::RenderWindow& window);
		std::ostringstream textStream;
		sf::Font font;

	private:
		sf::Text textVisual;
		sf::RectangleShape boxVisual;
		void deleteLastChar();
};

