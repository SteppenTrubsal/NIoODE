#include <vector>
#include <string>
//#include <muParser.h>
#include <cmath>
using namespace std;

/*double fun(string& fun, double x) {
	mu::Parser parser;
	parser.SetExpr(fun);
	parser.DefineVar("x", &x);
	return parser.Eval();
}*/
double fun(string& fun, double x) {
	return 3 * cos(2 * 3.141592 * x);
}