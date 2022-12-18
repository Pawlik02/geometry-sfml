#pragma once
#include <iostream>

class Point
{
	public:
		double x, y;
		Point(double x=0.0, double y=0.0);
		~Point();
		friend std::ostream& operator<<(std::ostream& os, Point& point);
};