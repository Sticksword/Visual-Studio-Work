#include "Point.h"
#include <string>
#include <cmath>

using namespace std;

Point::Point(){

}

Point::Point(double a, double b){
	x = a;
	y = b;

}

double Point::getX(){
	return x;
}

double Point::getY(){
	return y;
}

double Point::getDistance(Point p){
	if (getX() == p.getX() && getY() == p.getY()) {
		return 10001;
	}
	return sqrt( pow((x - p.getX()), 2) + pow((y - p.getY()), 2) );
}