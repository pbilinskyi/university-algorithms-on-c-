#pragma once
#include <ostream>

//can be interpreted as vector with origin in (0,0)
struct Point {
	double x, y;
	Point();
	Point(double, double);

	Point operator*(const double k) const;
	Point operator+(const Point& B) const;
	Point operator-(const Point& B) const;
	
	friend std::ostream& operator<<(std::ostream&, const Point&);
	bool operator<(const Point&) const;

	//dot product
	double operator*(const Point& B) const;

	//as of vector
	double norm() const;
	//double polarAngle() const;
};

Point linearCombination(double a, const Point& A, double b, const Point& B);

double dist(const Point& A, const Point& B);

double angle(const Point& A, const Point& B, const Point& C);

double det(const Point& A, const Point& B);

double det(const Point& origin, const Point& A, const Point& B);


/*template <typename T>
double det(T x1, T y1, T x2, T y2);

//==========================
template<typename T>
inline double det(T x1, T y1, T x2, T y2)
{
	return x1*y2 - x2*y1;
}
*/