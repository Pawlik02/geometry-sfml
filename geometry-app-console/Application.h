#pragma once
#include <SFML/Graphics.hpp>
#include "Polygon.h"
#include "TextBox.h"
#include <iostream>

class Application
{
	public:
		Application();
		~Application();
		void start();

	private:
		sf::RenderWindow window = { sf::VideoMode(1000, 600), "Geometry SFML" };
		std::vector<Polygon> shapesList;
		template<typename shapeType>
		void addShape(shapeType shape);
		void createPolygon(sf::Event event, TextBox& textBox);
};