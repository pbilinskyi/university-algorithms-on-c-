#define _USE_MATH_DEFINES

#include "Random.h"
#include <iostream>
#include "time.h"
#include <cmath>

int EuclidExtended(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		//cout << "a = " << a << "\tb = " << b << "\tx = " << x << "\ty = " << y << endl;
		return a;
	}
	else {
		int d = EuclidExtended(b, a % b, x, y);
		int temp = y;
		y = x - y * (a / b);
		x = temp;
	//	cout << "a = " << a << "\tb = " << b << "\tx = " << x << "\ty = " << y << endl;
		return d;
	}
}

int ReciprocalByModule(int a, int p) {
	int x, y;
	EuclidExtended(p, a, x, y);
	return (y % p + p) % p;
}

void testEuclid() {
	cout << "=======	Test Euclid:	==========" << endl;
	//int x = 0, y = 0;
	//cout << "GCD = " << EuclidExtended(99, 37, x, y) << endl;
	cout << " === " << ReciprocalByModule(5602, 9973) << endl;

	cout << "=======	Test Finished:	==========" << endl;
}

int nearestPowerOf2(int n) {
	return static_cast<int>(pow(2, floor(log(RANGE) / log(2))));
}

LinearCongruential::LinearCongruential(){
	srand(time(0));
	x_prev = rand() % m;
}
LinearCongruential::LinearCongruential(int x0) : x_prev(x0) {}


double LinearCongruential::next() noexcept {
	int x_cur = (a*x_prev + c) % m;
	x_prev = x_cur;
	return (static_cast<double>(x_cur)) / m;
}

QuadraticalCongruential::QuadraticalCongruential(){
	srand(time(0));
	x_prev = rand() % m;
}

QuadraticalCongruential::QuadraticalCongruential(int x0) : x_prev(x0) {}

double QuadraticalCongruential::next() noexcept {
	int x_cur = (d*x_prev*x_prev + a*x_prev + c) % m;
	x_prev = x_cur;
	return (static_cast<double>(x_cur)) / m;
}

double Fibonacci::next() noexcept{
	int x_2 = (x_0 + x_1) % m;
	x_0 = x_1;
	x_1 = x_2;
	return (static_cast<double>(x_2)) / m;
}

Fibonacci::Fibonacci() : x_0(1), x_1(1) {}

ReciprocalCongruential::ReciprocalCongruential()
{
	srand(time(0));
	x_prev = rand() % p;
}

ReciprocalCongruential::ReciprocalCongruential(int x0) : x_prev(x0) {}

double ReciprocalCongruential::next() noexcept
{
	int x_cur = (a*ReciprocalByModule(x_prev, p) + c) % p;
	x_prev = x_cur;
	return static_cast<double>(x_cur)/p;
}


double ThreeSigmaRule::next() noexcept
{
	init();
	double temp = ((m + (sum - 6)*sigma) + 3) / 6;
	return temp;
}

void ThreeSigmaRule::init() noexcept
{
	sum = 0;
	for (int i = 0; i < 12; ++i) {
		sum += lc.next();
	}

}

double PolarCoordMethod::next() noexcept
{
	if (!flag) { return (3 + X2) / 6; }
	
	else {
		double V1, V2, S;
		do {
			V1 = 2 * lc.next() - 1,
			V2 = 2 * lc.next() - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1);

		double k = sqrt(-2 * log(S) / S);
		X1 = V1 * k;
		X2 = V2 * k;

		return (3 + X1)/6;
	}
}


double RatioMethod::next() noexcept
{
	double U = 0, V, X;
	do {
		while (U == 0) U = lc.next();
		V = lc.next();

		X = sqrt(8 / M_E) * (V - 0.5) / U;
	} while (X*X > -4*log(U));
	
	return (radius + X) / (2*radius);
}

double LogarithmMethod::next() noexcept
{
	return -miu * log(lc.next()) / highLimit;
}

double ArenseMethod::next() noexcept
{
	double X = 0, Y = 0, V = 0;
	do {
		do {
			Y = tan(M_PI * lc.next());
			X = sqrt(2 * a - 1)*Y + a - 1;
		} while (X <= 0);
		V = lc.next();
	} while (V > (1 + Y * Y)*exp((a - 1)*log(X / (a - 1)) - sqrt(2 * a - 1)*Y));

	return (X - low_border)/dist;
}

double UnitionMethod::next() noexcept
{
	int X = static_cast<int>((m*lc.next()));
	int Y = static_cast<int>((m*lc.next()));
	//int Z = (X - Y) % m;
	int Z = static_cast<int>((1 + lc.next() - lc.next())*(m/2)) % m;
	return static_cast<double>(Z) / m;
}
