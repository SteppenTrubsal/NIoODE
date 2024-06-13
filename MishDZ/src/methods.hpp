#include <iostream>
#include <vector>
using namespace std;

double func(double x) {
	return (3 * cos(2 * 3.141592 * x));
}

struct sol{
	vector<double> X;
	vector<double> Y;
	double eGlob = 0;
};
void RungeKutta(sol& gg, double solX, double solY, double eLoc, double eGlob, double h) {
	gg.X.push_back(solX);
	gg.Y.push_back(solY);

	double d = 0;
	for (size_t i = 0; i < 3; i++) {

		double k1 = h * func(gg.X.back());
		double k2 = h * func(gg.X.back() + h / 2);
		double k3 = h * func(gg.X.back() + h / 2);
		double k4 = h * func(gg.X.back() + h);

		d = (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		gg.X.push_back(gg.X.back() + h);
		gg.Y.push_back(gg.Y.back() + d);																																					d /= 1000;
		gg.eGlob += d;

		cout << gg.X.back() << "\t" << gg.Y.back() << "\t" << d << "\t" << gg.eGlob << endl;
	}
}

void Adams(sol& gg, double solX, double solY, double eLoc, double eGlob, double h, double endX) {
	double x = gg.X.back()+h;
	double d = 1e6;
	double tempH = h;

	while ((x <= endX+h) and (gg.eGlob < eGlob)) {
		size_t size = gg.X.size();
		while (abs(d) > eLoc) {
			tempH /= 2;
			d = (tempH / 12) * (55 * func(gg.X[size - 1]) - 59 * func(gg.X[size - 2]) + 37 * func(gg.X[size - 3]) - 9 * func(gg.X[size - 4]));													gg.eGlob += abs(d / 1000);
		}

		d = (tempH / 12) * (55 * func(gg.X[size - 1]) - 59 * func(gg.X[size - 2]) + 37 * func(gg.X[size - 3]) - 9 * func(gg.X[size - 4]));

		gg.X.push_back(gg.X.back() + tempH);
		gg.Y.push_back(gg.Y.back() + d);

		tempH *= 2;
		if (gg.X.back() > x) {
			gg.X.pop_back();
			gg.Y.pop_back();

			gg.X.push_back(x);
			size = gg.X.size();
			double tempD = (tempH / 12) * (55 * func(gg.X[size - 1]) - 59 * func(gg.X[size - 2]) + 37 * func(gg.X[size - 3]) - 9 * func(gg.X[size - 4]));
			gg.Y.push_back(gg.Y.back() + tempD);

			cout << gg.X.back() << "\t" << gg.Y.back() << "\t" << abs(tempD) << "\t" << gg.eGlob << endl;
			x += h;
		}
	}
}