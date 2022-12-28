#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	public: 
		Button(sf::Vector2f size, sf::Vector2f position, sf::Color color);
		void draw(sf::RenderWindow& window);
		bool isMouseOver(sf::RenderWindow& window);

	private:
		sf::RectangleShape buttonVisual;
};