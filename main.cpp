#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

static const double M_PI = 3.14159265358979323846;

double const sinRatio(const double, const int);
double const cosRatio(const double, const int);
double const expRatio(const double, const int);
double const lnxminus1Ratio(const double, const int);
double const atanRatio(const double, const int);
double const loopCalc(double, const double(*) (const double, const int), double, double = 0, int = 0);

int main() {
	cout << setprecision(10) ;
	while (true) {
		cout << "Which function do you want to calculate?" << endl
			<< "1 >> Sin x" << endl
			<< "2 >> Cos x" << endl
			<< "3 >> Tan x" << endl
			<< "4 >> Csc x" << endl
			<< "5 >> Sec x" << endl
			<< "6 >> Cot x" << endl
			<< "7 >> Ln x" << endl
			<< "8 >> Exp(x)" << endl
			<< "9 >> Arctan(x)" << endl;
		int choice;
		cin >> choice;
		double x;
		cout << "Enter x: " << endl;
		cin >> x;
		if (choice < 7)
			x = fmod(x, 2 * M_PI);

		if (choice == 1) {
			cout << loopCalc(x, sinRatio,x);
		}
		else if (choice == 2) {
			cout << loopCalc(x, cosRatio,1);
		}
		else if (choice == 3) {
			double sin = loopCalc(x, sinRatio, x);
			double cos = loopCalc(x, cosRatio, 1);
			cout << sin / cos;
		}
		else if (choice == 4) {
			cout << 1 / loopCalc(x, sinRatio, x);
		}
		else if (choice == 5) {
			cout << 1 / loopCalc(x, cosRatio, 1);
		}
		else if (choice == 6) {
			double sin = loopCalc(x, sinRatio, x);
			double cos = loopCalc(x, cosRatio, 1);
			cout << cos / sin;
		}
		else if (choice == 7) {
			if (x <= 0) {
				cout << "Result does not exist" << endl;
				continue;
			}
			else if (x >= 2) {
				cout << "Result not computable by the Maclaurin series" << endl;
				continue;
			}
			x = 1 - x;
			double minus1 = loopCalc(x, lnxminus1Ratio, -x);
			cout << minus1;
		}
		else if (choice == 8) {
			cout << loopCalc(x, expRatio, 1);
		}
		else if (choice == 9) {
			if (x < -1 || x > 1) {
				cout << "Result not computable by the Maclaurin series" << endl;
				continue;
			}
			cout << loopCalc(x, atanRatio, x);
		}
		cout << endl;
	}
}

double const sinRatio(const double x, const int n) {
	return -x * x / ((2 * n + 3)*(2 * n + 2));
}
double const cosRatio(const double x, const int n) {
	return -x * x / ((2 * n + 2)*(2 * n + 1));
}
double const expRatio(const double x, const int n) {
	return x / (n + 1);
}
double const lnxminus1Ratio(const double x, const int n) {
	return x * (n + 1) / (n + 2);
}
double const atanRatio(const double x, const int n) {
	return -x * x * (2 * n + 1) / (2 * n + 3);
}
/*
* x is the value of the function
* ratio is a pointer to the ratio function, it takes x and the current value of n
* currVal, first call is the initial value of the summation, usually either 1 or x.
later calls is the previous term.
* sum is the total sum thus far.
* i is the current value of n
*/
double const loopCalc(double x, const double(*ratio) (const double, const int), double currVal, double sum, int i) {
	if (fabs(currVal) < 1e-10 || i > 4000)
		return sum;
	else
		return loopCalc(x, ratio, currVal * ratio(x, i), sum + currVal, i + 1);
}
