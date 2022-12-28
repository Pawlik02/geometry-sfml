#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class Figure: public sf::Shape
{
	public:
		std::string name;
		Button menuButton;
};