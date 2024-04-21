#include "methods.hpp"
using namespace std;

int main() {
	double a = 2.718, b = 5.718;
	double solX = 2.718, solY = 2;
	string func = "(1/(x*y))*(y^2/(ln(x))-1)";
	string analSolution = "y=sqrt(2*(ln(x))^2+2*ln(x))";

	double h = 1;

	//getResultGraphics(a, b, solY, func, 0.1, analSolution);
	//getDiffGraph(a, b, 10, solY, func, analSolution);
	mulThreadDiffGraph(a, b, 100, solY, func, analSolution);
	return 0;
}