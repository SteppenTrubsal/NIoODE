#include "someFunc.hpp"

struct graph {
	vector<double> X;
	vector<double> Y;
	vector<double> Eloc;
	vector<double> Eglob;
};

void RungeKutta(graph& gr, double startX, double startY, double eLoc, double eGlob, double h, string& func, bool& flag) {
	gr.X.push_back(startX);
	gr.Y.push_back(startY);
	gr.Eglob.push_back(0);
	gr.Eloc.push_back(0);
	double k1, k2, k4, k, d;
	double tempH = h;
	while (gr.Eglob.back() < eGlob) {
		double tempX = gr.X.back(), tempY = gr.Y.back();
		tempX += tempH;
		k1 = tempH * fun(func, tempX);
		k2 = tempH * fun(func, tempX + tempH/2);
		k4 = tempH * fun(func, tempX + tempH);
		k = (k1 + 4 * k2 + k4) / 6;
		d = abs(k);
		if (d > eLoc) {
			tempH /= 2;
		}
		else {
			tempH *= 2;
			gr.X.push_back(tempX);
			gr.Y.push_back(tempY + k);
			gr.Eloc.push_back(d);
			gr.Eglob.push_back(gr.Eglob.back() + d);
			cout << gr.X.back() << "\t" << gr.Y.back() << "\t" << gr.Eloc.back() << "\t" << gr.Eglob.back() << endl;
		}
		if (gr.X.size() >= 5) { 
			flag = true;
			break; 
		}
	}
}

void Adams(graph& gr, double endX, double eLoc, double eGlob, double h, string& func, bool& flag) {
	if (flag) {
		flag = false;
		double tempH = h;
		double delta, d;
		while (gr.Eglob.back() < eGlob) {
			double tempX = gr.X.back(), tempY = gr.Y.back();
			tempX += tempH;
			delta = (tempH / 24) * (55 * fun(func, gr.X.back()) - 59 * fun(func, gr.X[gr.X.size() - 2]) + 37 * fun(func, gr.X[gr.X.size() - 3]) - 9 * fun(func, gr.X[gr.X.size() - 4]));
			d = abs(delta);
			if (d > eLoc) {
				tempH /= 2;
			}
			else {
				tempH *= 2;
				gr.X.push_back(tempX);
				gr.Y.push_back(tempY + delta);
				gr.Eloc.push_back(d);
				gr.Eglob.push_back(gr.Eglob.back() + d);
				cout << gr.X.back() << "\t" << gr.Y.back() << "\t" << gr.Eloc.back() << "\t" << gr.Eglob.back() << endl;
			}
			if (tempX >= endX) {
				flag = true;
				break;
			}
		}
	}
}