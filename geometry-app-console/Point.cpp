#include "Point.h"
#include <iostream>

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

Point::~Point() {
	std::cout << "Point destructor\n";
}

std::ostream& operator<<(std::ostream& os, Point& point) {
	os << "Point(" << point.x << ", " << point.y << ")\n";
	return os;
}