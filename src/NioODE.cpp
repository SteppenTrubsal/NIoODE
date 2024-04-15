#include "methods.hpp"
using namespace std;

int main() {
	double a = 2, b = 5;
	double solX = 2, solY = 3;
	string func = "(1/2*x)*(y-1+x^2/(y-1))";

	double h = 1;

	EulerGraph(a, b, solY, func, h);
	thirdAdamsMethod(a, b, solY, func, h);
}