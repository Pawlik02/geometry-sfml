#include "Figure.h"

Figure::Figure(std::string name) {
	this->name = name;
}

std::ostream& operator<<(std::ostream& out, Figure& figure) {
	out << figure.print();
	return out;
}