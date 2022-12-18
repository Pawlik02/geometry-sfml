#pragma once
#include <iostream>
#include "Point.h"

class Polygon
{
	public:
		Polygon(std::string name, Point verticies[]);
		~Polygon();
		std::string name;
		Point* verticies;
};

