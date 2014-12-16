#include "Point.h"
#include <string>

using namespace std;

Point::Point(){

}

Point::Point(float a, float b, string s){
	x = a;
	y = b;
	category = s;
}

float Point::getX(){
	return x;
}

float Point::getY(){
	return y;
}

string Point::getCategory(){
	return category;
}

void Point::setDistance(float input){
	distance = input;
}

float Point::getDistance(){
	return distance;
}