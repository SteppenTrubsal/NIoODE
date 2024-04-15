#include "someFunc.hpp"
using namespace std;

void Euler(double h, string& func, vector<double>& X, vector<double>& Y) {
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
	Euler(h, func, res.x, res.y);
	return res;
}

void RungeKutta(double h, string& func, vector<double>& X, vector<double>& Y) {
	for (int i = 0; i < X.size() - 1; i++) {
		double k1 = h * fun(func, X[i], Y[i]);
		double k2 = h * fun(func, X[i] + h / 2, Y[i] + k1 / 2);
		double k3 = h * fun(func, X[i] + h / 2, Y[i] + k2 / 2);
		double k4 = h * fun(func, X[i] + h, Y[i] + k3);
		Y[i + 1] = Y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}
}
graph RungeKuttaGraph(double a, double b, double sol, string& func, double h) {
	graph res;
	res.name = "Runge-Kutta method";
	res.x = getX(a, b, h);
	res.y = vector<double>(res.x.size());
	res.y[0] = sol;
	RungeKutta(h, func, res.x, res.y);
	return res;
}

void secondAdams(double h, string& func, vector<double>& X, vector<double>& Y) {
	for (int i = 1; i < X.size() - 1; i++) {
		Y[i + 1] = Y[i] + (h / 2) * (3 * fun(func, X[i], Y[i]) - fun(func, X[i - 1], Y[i - 1]));
	}
}
graph secondAdamsMethod(double a, double b, double sol, string& func, double h) {
	graph res;
	res.name = "Two-step Adams method";
	res.x = getX(a, b, h);
	res.y = vector<double>(res.x.size());
	res.y[0] = sol;
	vector<double> x01 = getSpline(res.x, 0, 2);
	RungeKutta(h, func, x01, res.y);
	secondAdams(h, func, res.x, res.y);
	return res;
}

void thirdAdams(double h, string& func, vector<double>& X, vector<double>& Y) {
	for (int i = 2; i < X.size() - 1; i++) {
		Y[i + 1] = Y[i] + (h / 12) * (23 * fun(func, X[i], Y[i]) - 16 * fun(func, X[i - 1], Y[i - 1]) + 5 * fun(func, X[i - 2], Y[i - 2]));
	}
}
graph thirdAdamsMethod(double a, double b, double sol, string& func, double h) {
	graph res;
	res.name = "Three-step Adams method";
	res.x = getX(a, b, h);
	res.y = vector<double>(res.x.size());
	res.y[0] = sol;
	vector<double> x01 = getSpline(res.x, 0, 3);
	RungeKutta(h, func, x01, res.y);
	thirdAdams(h, func, res.x, res.y);
	return res;
}