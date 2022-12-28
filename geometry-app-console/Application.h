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
		sf::RenderWindow window = { sf::VideoMode(800, 800), "Geometry SFML" };
		std::vector<Figure*> figuresList;
		bool isFigureSelected = false;
		Figure* selectedFigure;
		void addFigure(Figure* figure);
		void deleteFigure();
		void reloadMenuButtons();
		void createPolygon(sf::Event event, TextBox& textBox, sf::Font& font);
};