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