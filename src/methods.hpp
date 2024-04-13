#include "someFunc.hpp"
using namespace std;

void Euler(double h, string& func, vector<double>& Y, vector<double>& X) {
	for (int i = 0; i < X.size()-1; i++) {
		Y[i+1] = Y[i] + h * fun(func, X[i], Y[i]);
	}
}
graph EulerGraph(double a, double b, double sol, string& func, double h) {
	graph res;
	res.name = "Euler method";
	res.x = getX(a, b, h);
	res.y = vector<double>(res.x.size());
	res.y[0] = sol;
	Euler(h, func, res.y, res.x);
	return res;
}