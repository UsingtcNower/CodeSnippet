#include <cmath>
#include <iostream>
using namespace std;

double mySqrt(double a) {
	double x=a;
	double last;
	do {
		last = x;
		x = (x+a/x)/2;
	}while(fabs(x-last)>1E-5);
	return x;
}

int main() {
	cout << mySqrt(9) << ", " << sqrt(9) << endl;
	cout << mySqrt(19) << ", " << sqrt(19) << endl;
}
