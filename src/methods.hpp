#include "someFunc.hpp"
#include <thread>
#include <mutex>
using namespace std;

void Euler(double h, string& func, vector<double>& X, vector<double>& Y) {
	for (size_t i = 0; i < X.size()-1; i++) {
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
	for (size_t i = 0; i < X.size() - 1; i++) {
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
	for (size_t i = 1; i < X.size() - 1; i++) {
		Y[i + 1] = Y[i] + (h / 2) * (3 * fun(func, X[i], Y[i]) - fun(func, X[i - 1], Y[i - 1]));
	}
}
graph secondAdamsGraph(double a, double b, double sol, string& func, double h) {
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
	for (size_t i = 2; i < X.size() - 1; i++) {
		Y[i + 1] = Y[i] + (h / 12) * (23 * fun(func, X[i], Y[i]) - 16 * fun(func, X[i - 1], Y[i - 1]) + 5 * fun(func, X[i - 2], Y[i - 2]));
	}
}
graph thirdAdamsGraph(double a, double b, double sol, string& func, double h) {
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

void analSol(double h, string& func, vector<double>& X, vector<double>& Y) {
	for (size_t i = 0; i < X.size(); i++) {
		Y[i] = oneArgFun(func, X[i]);
	}
}
graph analSolGraph(double a, double b, string& func, double h) {
	graph res;
	res.name = "Analythical solution";
	res.x = getX(a, b, h);
	res.y = vector<double>(res.x.size());
	analSol(h, func, res.x, res.y);
	return res;
}

vector<graph> getResultGraphics(double a, double b, double sol, string& func, double h, string& analSol) {
	vector<graph> result(5);
	eqRebuild(analSol);

	result[0] = EulerGraph(a, b, sol, func, h);
	result[1] = RungeKuttaGraph(a, b, sol, func, h);
	result[2] = secondAdamsGraph(a, b, sol, func, h);
	result[3] = thirdAdamsGraph(a, b, sol, func, h);
	result[4] = analSolGraph(a, b, analSol, h);

	return result;
}

vector<graph> getDiffGraph(double a, double b, double n, double sol, string& func, string& analSol) {
	double hMax = (b - a) / 10;
	double hMin = (b - a) / 1000;
	double it = (hMax - hMin) / n;

	vector<graph> diffGraphics(4);
	vector<double> H;

	for (; hMin < hMax; hMin += it) {
		H.push_back(hMin);
	}
	for (size_t i = 0; i < H.size(); i++) {
		vector<graph> temp = getResultGraphics(a, b, sol, func, H[i], analSol);
		for (size_t j = 0; j < diffGraphics.size(); j++) {
			diffGraphics[j].x.push_back(H[i]);
		}
		diffGraphics[0].y.push_back(getDiff(temp[0], temp[4]));
		diffGraphics[1].y.push_back(getDiff(temp[1], temp[4]));
		diffGraphics[2].y.push_back(getDiff(temp[2], temp[4]));
		diffGraphics[3].y.push_back(getDiff(temp[3], temp[4]));
	}
	return diffGraphics;
}

vector<graph> mulThreadDiffGraph(double a, double b, double n, double sol, string& func, string& analSol) {
	double hMax = (b - a) / 10;
	double hMin = (b - a) / 1000;
	double it = (hMax - hMin) / n;

	vector<graph> diffGraphics(4);
	vector<double> H;

	for (; hMin < hMax; hMin += it) {
		H.push_back(hMin);
	}

}