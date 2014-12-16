#ifndef _POINT_H_
#define _POINT_H_
#include <string>
using namespace std;

class Point {
	float x;
	float y;
	string category;
	float distance;

public:
	Point();
	Point(float, float, string);
	float getX();
	float getY();
	string getCategory();
	void setDistance(float distance);
	float getDistance();
};

#endif