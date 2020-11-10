#pragma once

#include <iostream>


using namespace std;

//last prime number before 10000
const long RANGE = 9973;

//pre: a >= b
int EuclidExtended(int a, int b, int& x, int& y);

//pre: gcd(a, p) = 1 && p > a
int ReciprocalByModule(int a, int p);

//watch the work of Extended Euclidean Algorithm implemented in EuclidExtended()
void testEuclid();

int nearestPowerOf2(int n);


class Random {
public:
	virtual double next() noexcept = 0;
};


class LinearCongruential : public Random {
public:
	LinearCongruential();
	LinearCongruential(int x0);
	double next() noexcept;
private:
	const int m = RANGE;
	const int c = 57;
	const int a = 15;
	int x_prev;
};

class QuadraticalCongruential : public Random {
public:
	QuadraticalCongruential();
	QuadraticalCongruential(int x0);
	double next() noexcept;
private:
	const long m = RANGE;
	const int d = 16;
	const int c = 57;
	const int a = 15;
	int x_prev;
};

class Fibonacci : public Random {
public:
	Fibonacci();
	double next() noexcept;
private:
	const int m = RANGE;
	int x_0;
	int x_1;
};

class ReciprocalCongruential : public Random {
public:
	ReciprocalCongruential();
	ReciprocalCongruential(int x0);
	double next() noexcept;
private:
	const int p = RANGE;
	const int c = 58;
	const int a = 7;
	int x_prev;
};

class UnitionMethod : public Random {
public:
	double next() noexcept;
private:
	LinearCongruential lc;
	const int m = RANGE;
};

class ThreeSigmaRule : public Random {
public:
	double next() noexcept;
	void init() noexcept;
private:
	LinearCongruential lc;
	double sum;
	const double sigma = 1;
	const double m = 0;
};

class PolarCoordMethod : public Random {
public:
	double next() noexcept;
private:
	LinearCongruential lc;
	bool flag = true;
	double X1, X2;
};

class RatioMethod : public Random{
public:	
	double next() noexcept;
private:
	LinearCongruential lc;
	const double radius = 5;
};


class LogarithmMethod : public Random {
public:
	double next() noexcept;
private:
	LinearCongruential lc;
	const double miu = 3 / 2;
	const double highLimit = 10;
};


class ArenseMethod : public Random {
public:
	double next() noexcept;
private:
	LinearCongruential lc;
	const int a = 9;
	const double dist = 18;
	const double low_border = 3.4;
};
