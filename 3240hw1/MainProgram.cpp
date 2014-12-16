#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<sstream>
#include<string>
#include "Point.h"
using namespace std;
// by Michael Chen - mzc2fd@virginia.edu

class MainProgram {
	int k;
	string filename;
	int m;
	vector<Point> dots;
	float xIn;
	float yIn;

public:
	void askInput();
	void readData();
	void compareData(float a, float b);
	vector<Point> mergeSort(vector<Point> vec);
	vector<Point> merge(vector<Point> left, vector<Point> right);
};

void MainProgram::askInput() {
	cout << "How many neighbors do you wish to test against?" << endl;
	cin >> k;
	cout << "What is the name of the file with the data input?" << endl;
	cin >> filename;
	cout << "How many values do you wish to be read from data file?" << endl;
	cin >> m;
	readData();
	cout << "Please enter the x value of the unclassified data value." << endl;
	cin >> xIn;
	cout << "Now please enter the y value of the unclassified data value." << endl;
	cin >> yIn;
	while (!(xIn == 1.0 && yIn == 1.0)) {
		compareData(xIn, yIn);
		cout << "Please enter the x value of another unclassified data value." << endl;
		cin >> xIn;
		cout << "Now please enter the y value of the unclassified data value." << endl;
		cin >> yIn;
	}
}

void MainProgram::readData() {
	int count = 0;
	string line;
	ifstream myfile(filename.c_str());
	if (myfile.is_open()) {
		while (getline(myfile, line) && count < m) {
			string category;
			float xLocation;
			float yLocation;
			stringstream ss;
			ss << line;
			ss >> category >> xLocation >> yLocation;
			Point p = Point(xLocation, yLocation, category);
			dots.push_back(p);
			m++;
		}
		myfile.close();
	}
	else {
		cout << "file not found" << endl;
		_exit(0);
	}
}

void MainProgram::compareData(float a, float b) {
	float distance;

	// base case for nearest neighbor algorithm
	float shortest = distance = sqrt(pow(a - dots[0].getX(), 2) + pow(b - dots[0].getY(), 2));;
	Point nearest;
	if (k == 1) {
		for (int i = 1; i < dots.size(); i++) {
			distance = sqrt(pow(a - dots[i].getX(), 2) + pow(b - dots[i].getY(), 2));
			if (distance < shortest){
				distance = shortest;
				nearest = dots[i];
			}
		}
	}

	// update dots with distance from unclassified point
	// then merge sort based on distance
	for (int i = 0; i < dots.size(); i++) {
		distance = sqrt( pow(a - dots[i].getX(), 2) + pow(b - dots[i].getY(), 2) );
		dots[i].setDistance(distance);
	}
	dots = mergeSort(dots);
	int blueCount = 0;
	float blueDistance = 0.0;
	int redCount = 0;
	float redDistance = 0.0;
	for (int i = 0; i < k; i++) {
		cout << dots[i].getCategory() << " " << dots[i].getX() << " " << dots[i].getY() << " " << dots[i].getDistance() << endl;
		if (dots[i].getCategory() == "blue"){
			blueCount++;
			blueDistance += dots[i].getDistance();
		}
		else {
			redCount++;
			redDistance += dots[i].getDistance();
		}
	}
	if (blueCount > redCount) {
		cout << "Data item (" << a << ", " << b << ") assigned to: blue" << endl;
	}
	else if (redCount > blueCount) {
		cout << "Data item (" << a << ", " << b << ") assigned to: red" << endl;
	}
	else {
		cout << "Since red and blue count are equal, we base off of avg distance." << endl;
		//if equal distance and occurence, we just say it is red
		if (redDistance >= blueDistance) {
			cout <<	"Data item (" << a << ", " << b << ") assigned to: red" << endl;
		}
		else {
			cout << "Data item (" << a << ", " << b << ") assigned to: blue" << endl;
		}
	}
	cout << "Average distance to red items: " << redDistance / redCount << endl;
	cout << "Average distance to blue items: " << blueDistance / blueCount << endl;
	

}

vector<Point> MainProgram::mergeSort(vector<Point> vec) {
	if (vec.size() == 1) {
		return vec;
	}
	// determine the location of the middle element in the vector
	vector<Point>::iterator middle = vec.begin() + (vec.size() / 2);
	vector<Point> left(vec.begin(), middle);
	vector<Point> right(middle, vec.end());

	// perform a merge sort on the two smaller vectors
	left = mergeSort(left);
	right = mergeSort(right);
	// this is the recursive part
	return merge(left, right);
}

vector<Point> MainProgram::merge(vector<Point> left, vector<Point> right){
	// fill the resultant vector with sorted results from both vectors
	vector<Point> result;
	unsigned left_it = 0, right_it = 0;
	while (left_it < left.size() && right_it < right.size()) {
		// if the left value is smaller than the right it goes next
		// into the resultant vector
		if (left[left_it].getDistance() < right[right_it].getDistance()) {
			result.push_back(left[left_it]);
			left_it++;
		}
		else {
			result.push_back(right[right_it]);
			right_it++;
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


int main() {
	MainProgram obj;
	obj.askInput();
	return 0;
}
