#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Polygon.h"
#include "Point.h"

int main() {
	int n;
	std::cin >> n;
	Point* points_arr = new Point[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		int x = rand() % 100 - 50;
		int y = rand() % 100 - 50;
		points_arr[i].x = x;
		points_arr[i].y = y;
	}
	for (int i = 0; i < n; i++) {
		std::cout << points_arr[i];
	}
	Polygon p1 = Polygon("polygon1", points_arr);
	delete[] points_arr;
}