#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	public: 
		Button();
		Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Font& font,
			std::string text="", int characterSize = 12);
		void draw(sf::RenderWindow& window);
		bool isMouseOver(sf::RenderWindow& window);
		void setColor(sf::Color color);
		void setPosition(sf::Vector2f position);

	private:
		sf::RectangleShape buttonVisual;
		sf::Text textVisual;
};