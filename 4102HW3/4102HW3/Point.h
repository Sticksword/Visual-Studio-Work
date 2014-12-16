#ifndef _POINT_H_
#define _POINT_H_
#include <string>
using namespace std;

class Point {
	double x;
	double y;

public:
	Point();
	Point(double, double);
	double getX();
	double getY();

	double getDistance(Point p);
};

#endif