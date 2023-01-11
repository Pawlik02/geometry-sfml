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
		std::vector<Button*> colorList;
		sf::Font getFont();
		void addFigure(Figure* figure);
		void createPolygon(std::string nameInput, std::string verticiesInput, sf::Color color);
		void createRectangle(std::string nameInput, std::string positionInput, std::string dimensionsInput, sf::Color color);
		void createCircle(std::string nameInput, std::string positionInput, std::string radiusInput, sf::Color color);
		void createSquare(std::string nameInput, std::string positionInput, std::string widthInput, sf::Color color);
		sf::Font font;
		int exceptionNumber = 1;

	private:
		static Application* instancePtr;
		Application();
		~Application();
		sf::RenderWindow window = { sf::VideoMode(800, 800), "Geometry SFML" };
		Figure* selectedFigure = nullptr;
		TextInput* selectedTextInput = nullptr;
		Button* selectedFigureType = nullptr;
		Button* selectedColor = nullptr;
		void reloadMenuButtons();
		void saveToFile(TextInput* fileNameInput);
		void loadFromFile(TextInput* fileNameInput);
};