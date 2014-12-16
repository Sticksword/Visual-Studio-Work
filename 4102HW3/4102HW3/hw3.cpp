#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "Point.h"
using namespace std;
// by Michael Chen - mzc2fd@virginia.edu

class hw3 {
	string filename;

public:
	void askInput(string name);
	void analyzeData();
	double findShortest(vector<Point> vec);
	double divide(vector<Point> vec);
	double combine(double a, vector<Point> vec);
	vector<Point> mergeSort(vector<Point> vec, string selector);
	vector<Point> merge(vector<Point> left, vector<Point> right, string selector);
};

void hw3::askInput(string name) {
	//cout << "What is the name of the file with the data input?" << endl;
	//cin >> filename;
	filename = name;
	analyzeData();

}

void hw3::analyzeData() {
	int count = 0;
	string line;
	vector<Point> planets;
	ifstream myfile(filename.c_str());
	double xLocation;
	double yLocation;
	bool skipFirst = true;
	if (myfile.is_open()) {
		while (getline(myfile, line, '\n')) {
			stringstream ss(line);
			vector<string> seglist;
			string segment;
			while (getline(ss, segment, ' ')){
				seglist.push_back(segment);
			}

			if (seglist.size() == 1){
				if (skipFirst){
					skipFirst = false;
					continue;
				}
				double result = findShortest(planets);
				if (result >= 10000) {
					cout << "infinity" << endl;
				}
				else {
					cout << fixed << setprecision(4) << result << endl; // here we do something to the list of planets/points
				}


				if (seglist[0] == "0"){
					
					exit(0);
				}
				planets.clear();
				continue;
			}
			xLocation = atof(seglist[0].c_str());
			yLocation = atof(seglist[1].c_str());
			Point p = Point(xLocation, yLocation);
			planets.push_back(p);
		}
		myfile.close();
	}
	else {
		cout << "file not found" << endl;
		exit(0);
	}
}

// ----------------above is UI------------below is number crunching stuff-----------

double hw3::findShortest(vector<Point> vec){
	vec = mergeSort(vec, "x");
	return divide(vec);
}

double hw3::divide(vector<Point> vec){
	if (vec.size() <= 1){
		return 10001;
	}
	if (vec.size() == 2){
		return vec[0].getDistance(vec[1]);
	}
	vector<Point>::iterator middle = vec.begin() + (vec.size() / 2);
	vector<Point> left(vec.begin(), middle);
	vector<Point> right(middle, vec.end());
	double midvalue = (left[left.size() - 1].getX() + right[0].getX()) / 2;
	vector<Point> deltaFromMiddle;
	double delta = fmin(divide(left), divide(right));
	
	// ----------------------------adding the points within delta of the middle divide value-------------------
	for (int i = 0; i < vec.size(); i++) {

		// mid divide below zero
		if (left[left.size() - 1].getX() < 0) {
			if (vec[i].getX() < 0) {
				if (fabs(fabs(vec[i].getX()) - fabs(left[left.size() - 1].getX())) <= delta) {
					deltaFromMiddle.push_back(vec[i]);
				}
			}
			else {
				if (fabs(left[left.size() - 1].getX()) + vec[i].getX() <= delta) {
					deltaFromMiddle.push_back(vec[i]);
				}
			}
		}
		// mid divide above or at zero
		else {
			if (vec[i].getX() < 0) {
				if (left[left.size() - 1].getX() +fabs(vec[i].getX()) <= delta) {
					deltaFromMiddle.push_back(vec[i]);
				}
			}
			else {
				if (fabs(left[left.size() - 1].getX() -vec[i].getX()) <= delta) {
					deltaFromMiddle.push_back(vec[i]);
				}
			}
		}
	}
	return combine(delta, deltaFromMiddle);
}

double hw3::combine(double a, vector<Point> vec){
	vec = mergeSort(vec, "y");
	if (vec.size() <= 1) {
		return a;
	}
	if (vec.size() == 2) {
		return fmin(a, vec[0].getDistance(vec[1]));
	}
	double d = vec[0].getDistance(vec[1]);
	if (vec.size() >= 7) {
		for (int i = 0; i < vec.size() - 7; i++) {
			if (d > vec[i].getDistance(vec[i + 1])) {
				d = vec[i].getDistance(vec[i + 1]);
			}
			if (d > vec[i].getDistance(vec[i + 2])) {
				d = vec[i].getDistance(vec[i + 2]);
			}
			if (d > vec[i].getDistance(vec[i + 3])) {
				d = vec[i].getDistance(vec[i + 3]);
			}
			if (d > vec[i].getDistance(vec[i + 4])) {
				d = vec[i].getDistance(vec[i + 4]);
			}
			if (d > vec[i].getDistance(vec[i + 5])) {
				d = vec[i].getDistance(vec[i + 5]);
			}
			if (d > vec[i].getDistance(vec[i + 6])) {
				d = vec[i].getDistance(vec[i + 6]);
			}
			if (d > vec[i].getDistance(vec[i + 7])) {
				d = vec[i].getDistance(vec[i + 7]);
			}
		}
	}
	else {
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < vec.size(); j++) {
				if (d > vec[i].getDistance(vec[j])) {
					d = vec[i].getDistance(vec[j]);
				}
			}
		}
	}
	return fmin(a, d);
}

// --------------below is my mergesort methods--------------------

vector<Point> hw3::mergeSort(vector<Point> vec, string selector) {
	if (vec.size() <= 1) {
		return vec;
	}
	// determine the location of the middle element in the vector
	vector<Point>::iterator middle = vec.begin() + (vec.size() / 2);
	vector<Point> left(vec.begin(), middle);
	vector<Point> right(middle, vec.end());
	// perform a merge sort on the two smaller vectors
	left = mergeSort(left, selector);
	right = mergeSort(right, selector);
	// this is the recursive part
	return merge(left, right, selector);
}

vector<Point> hw3::merge(vector<Point> left, vector<Point> right, string selector){
	// fill the resultant vector with sorted results from both vectors
	vector<Point> result;
	unsigned left_it = 0, right_it = 0;
	while (left_it < left.size() && right_it < right.size()) {
		// if the left value is smaller than the right it goes next
		// into the resultant vector
		// sort by y
		if (selector == "y") {
			if (left[left_it].getY() < right[right_it].getY()) {
				result.push_back(left[left_it]);
				left_it++;
			}
			else {
				result.push_back(right[right_it]);
				right_it++;
			}
		}
		// sort by x
		else {
			if (left[left_it].getX() < right[right_it].getX()) {
				result.push_back(left[left_it]);
				left_it++;
			}
			else {
				result.push_back(right[right_it]);
				right_it++;
			}
		}
	}
	// push the remaining data from both vectors onto the resultant
	while (left_it < left.size()) {
		result.push_back(left[left_it]);
		left_it++;
	}
	while (right_it < right.size()) {
		result.push_back(right[right_it]);
		right_it++;
	}
	return result;
}


int main(int argc, char* args[]) {
	hw3 obj;
	obj.askInput(args[1]);
	return 0;
}