#include "src/methods.hpp"
#include <iostream>
using namespace std;



int main() {
	string func = "3*cos(2*3.141592*x)";
	double solX = 0, solY = 0;
	double endX = 2;
	double eGlob = 1e10, eLoc = 1e-6;
	double h = 0.01;
	bool goodEnding = false;

	graph test;
	cout << "xi\t" << "yi\t" << "Eloc\t" << "Eglob" << endl;
	RungeKutta(test, solX, solY, eLoc, eGlob, h, func, goodEnding);
	Adams(test, endX, eLoc, eGlob, h, func, goodEnding);

	cout << "Is this good ending?: " << goodEnding << endl;
	cout << "xi\t" << "yi\t" << "Eloc\t" << "Eglob" << endl;
	for (size_t i = 0; i < test.X.size(); i++) {
		//cout << test.X[i] << "\t" << test.Y[i] << "\t" << test.Eloc[i] << "\t" << test.Eglob[i] << endl;
	}
}