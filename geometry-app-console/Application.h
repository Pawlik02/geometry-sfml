#pragma once
#include <SFML/Graphics.hpp>
#include "Polygon.h"
#include "TextInput.h"
#include <iostream>

class Application
{
	public:
		Application(const Application& obj) = delete;
		static Application* getInstance();
		void start();
		void deleteFigure(std::string name="");
		std::vector<Figure*> figuresList;
		std::vector<TextInput*> textInputList;
		std::vector<Button*> buttonList;
		sf::Font getFont();
		void addFigure(Figure* figure);
		void createPolygon(TextInput* nameInput, TextInput* verticiesInput);
		void createRectangle(TextInput* nameInput, TextInput* positionInput, TextInput* dimensionsInput);
		void createCircle(TextInput* nameInput, TextInput* positionInput, TextInput* radiusInput);
		void createSquare(TextInput* nameInput, TextInput* positionInput, TextInput* widthInput);
		sf::Font font;

	private:
		static Application* instancePtr;
		Application();
		~Application();
		sf::RenderWindow window = { sf::VideoMode(800, 800), "Geometry SFML" };
		Figure* selectedFigure = nullptr;
		TextInput* selectedTextInput = nullptr;
		Button* selectedFigureType = nullptr;
		void reloadMenuButtons();
};