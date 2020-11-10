#define _USE_MATH_DEFINES
#include "geometryBasic.h"
#include <cmath> 


Point linearCombination( double a, const Point & A, double b, const Point & B)
{
	return Point(a * A.x + b * B.x, a * A.y + b * B.y);
}


double dist(const Point & A, const Point & B)
{
	return sqrt((A - B)*(A - B));
}

//origin - (0,0)
double angle(const Point & A, const Point & B)
{
	return acos((A*B) / (A.norm() * B.norm()));
}

//origin - B
double angle(const Point & A, const Point & B, const Point & C)
{
	return angle(A - B, C - B);
}

double det(const Point & A, const Point & B)
{
	return (A.x * B.y - B.x * A.y);
}

double det( const Point& A, const Point& origin, const Point& B) {
	return det(A - origin, B - origin);
}


Point::Point(): x(0), y(0){}

Point::Point(double x0, double y0): x(x0), y(y0){}

double Point::norm() const
{
	return sqrt((*this) * (*this));
}

Point Point::operator*(const double k) const
{
	return Point(x*k, y*k);
}

Point Point::operator+(const Point & B) const
{
	return linearCombination(1, *this, 1, B);
}

Point Point::operator-(const Point & B) const
{
	return linearCombination(1, *this, -1, B);
}

double Point::operator*(const Point & B) const
{
	return x*B.x + y*B.y;
}

std::ostream& operator<<(std::ostream& os, const Point& P) {
	return os << "(" << P.x << ", " << P.y << ")";
}


bool Point::operator<(const Point& P_other)const {
	double d = det(*this, P_other);
	return (d > 0) || ((d == 0) && (y < P_other.y));
}




