#include <vector>
#include <muParser.h>
using namespace std;

double fun(string& fun, double x, double y) {
	mu::Parser parser;
	parser.SetExpr(fun);
	parser.DefineVar("x", &x);
	parser.DefineVar("y", &y);
	return parser.Eval();
}
double oneArgFun(string& fun, double x) {
	mu::Parser parser;
	parser.SetExpr(fun);
	parser.DefineVar("x", &x);
	return parser.Eval();
}
void eqRebuild(string& s) {
	int equalSign = s.find('=');
	string right = s.substr(equalSign + 1);
	s.clear();
	s = right;
}

struct graph {
	vector<double> x;
	vector<double> y;
	string name;
};

vector<double> getX(double a, double b, double h) {
	vector<double> X;
	double x = a;
	for (; x <= b; x += h) {
		X.push_back(x);
	}
	return X;
}

vector<double> getSpline(vector<double> n, int st, int fn) {
	return vector<double>(n.begin() + st, n.begin() + fn);
}

double getDiff(graph a, graph b) {
	double diff = 0;
	for (int i = 0; i < a.x.size(); i++) {
		diff = (diff > abs(a.y[i] - b.y[i])) ? diff : abs(a.y[i] - b.y[i]);
	}
	return diff;
}