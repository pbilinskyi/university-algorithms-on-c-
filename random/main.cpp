#include <iostream>
#include "Histogram.h"
#include "Random.h"

using namespace std;

void findBorders(Random* rand) {

	double max = -100, min = 100, x;

	for (size_t i = 0; i < 10000; ++i) {
		x = rand->next();
		if (x > max) max = x;
		if (x < min) min = x;
	}
	cout << "MAX " << max << endl;
	cout << "MIN " << min << endl;
}


void   perform(Random* rand) {
	size_t N;
	cout << " Enter the number of random numbers: ";
	cin >> N;
	if (!cin) cout << "Error in input occured. Please, enter the positive integer number.";
/*
	for (size_t i = 0; i < N; ++i) {
		cout << rand->next() << endl;
	}
*/
	else {
		Histogram hist;
		for (size_t i = 0; i < N; ++i) {
			hist.add(rand->next()); 
		}
		hist.show();
	}
	
}

int main() {
	//LinearCongruential rand;
	//QuadraticalCongruential rand;
	//Fibonacci rand;
	//ReciprocalCongruential rand;
	//UnitionMethod rand;
	//ThreeSigmaRule rand;
	//PolarCoordMethod rand;
	//RatioMethod rand;
	LogarithmMethod rand;
	//ArenseMethod rand;
	perform(&rand);
	
	system("pause");
	return 0;
}