#include "Arc.h"
#include <stdexcept>
#include <cmath>
#include <utility>

int Arc::getKey() const noexcept{
	return key;
}

std::ostream& operator<<(std::ostream & os, const Arc &a) {
	os << "(" << a.left->P.x << ", " << a.left->P.y << ") - - - (" << a.right->P.y << ", " << a.right->P.y << ")"<<std::endl;
	return os;
}

void Arc::modify(float y_d) noexcept
{
	this->y_d = y_d;
	a = 1 / (2 * (f.y - y_d));
	b = -f.x * 2 * a;
	c = (f.y + y_d) / 2 + f.x*f.x * a;
	init();
}


Arc::Arc(sf::Vector2f & focus, float y_d, Edge* left, Edge* right, int key_i): key(key_i)
{
	f = focus;
	this->y_d = y_d;
	this->left = left;
	this->right = right;
	a = 1 / (2 * (f.y - y_d));
	b = -f.x * 2 * a;
	c = (f.y + y_d) / 2 + f.x*f.x * a;
}

/*bool Arc::operator<(const Arc & other)
{
	return this->left.x < other.left.x;
}
*/


void Arc::init()
{
	float x_left = left->P.x;
	float x_right = right->P.x;
	if (f.y != y_d) {
		arr.setPrimitiveType(sf::LineStrip);
		arr.resize(countApprLines);

		arr[0].position = sf::Vector2f(x_left, atX(x_left));
		arr[countApprLines - 1].position = sf::Vector2f(x_right, atX(x_right));

		arr[0].color = parabolaColor;
		arr[countApprLines - 1].color = parabolaColor;


		float step = (x_right - x_left) / (countApprLines - 1);
		float x = x_left + step;
		for (size_t i = 1; i < countApprLines - 1; ++i, x += step) {
			arr[i].position = sf::Vector2f(x, atX(x));
			arr[i].color = parabolaColor;
		}
	}
	else {
		arr.setPrimitiveType(sf::Lines);
		arr.resize(2);
		arr[0] = sf::Vector2f(f.x, 0);
		arr[0].color = parabolaColor;
		arr[1] = f;
		arr[1].color = parabolaColor;

	}
}

void Arc::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// draw the vertex array
	target.draw(arr, states);
}

float Arc::atX(float x) const noexcept
{
	return a*x*x + b*x + c;
}

void Arc::setColor(sf::Color &new_color) noexcept
{
	parabolaColor = new_color;
}

/*Edge::Edge(sf::Vector2f normal, sf::Vector2f point)
{
	if (normal.y != 0)	k = -normal.x / normal.y;
	else k = 
	b = -k * point.x + point.y;
	x0 = point;
}

float Edge::atX(float x)
{
	return k*x + b;
}
*/

sf::Color Edge::lineColor = sf::Color::White;

void Edge::init() {
	line[0] = { origin };
	line[1] = { P };
	line->color = lineColor;
}

//REPAIR IT!!!!
void Edge::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(line, 2, sf::Lines);
}

Edge::Edge(sf::Vector2f p0, sf::Vector2f n, sf::Vector2f dir_init ): origin(p0), P(p0), dir(dir_init){
	a = n.x;
	b = n.y;
	c = -n.x*p0.x - n.y*p0.y;
}

/*Edge::Edge(float a, float b, float c, sf::Vector2f P) : origin(P) {
	this->a = a;
	this->b = b;
	this->c = c;

}
*/
/*Edge::Edge(float x, float y)
{
	P1.x = x;
	P1.y = y;
	P0 = P1;
}
*/
void Edge::moveTo(sf::Vector2f dest)
{
	P = dest;
	init();
}

void Edge::scale(float scalar)
{
	P = scalar * dir + origin;
	init();
}

Edge Edge::operator-() const
{
	return Edge(origin, { a, b }, -dir);
}

float Edge::atX(float x)
{
	if (b == 0) throw std::logic_error("cannot compute atX() for this type of line: it is paralel to Y axis");
	return (- a/b)*x -(c / b);
}



//finds point of intersection of two parabolas with common directrix
sf::Vector2f intersection(sf::Vector2f& f1, sf::Vector2f& f2, float y_d, bool returnGreatest)
{
	float x;
	float d1 = f1.y - y_d;
	float d2 = f2.y - y_d;

	float a = 0.5f / d1 - 0.5f / d2,
		k = f2.x / (2 * d2) - f1.x / (2 * d1),
		c = f1.x*f1.x / (2 * d1) - f2.x*f2.x / (2 * d2) + 0.5f * (d1 - d2);
	
	if (a != 0) {
		float D = k * k - a * c;

		if (D < 0) throw std::logic_error("Discriminant < 0");
		else {
			if (returnGreatest) x = std::max((-k + sqrt(D)) / a, (-k - sqrt(D)) / a);
			else x = std::min((-k + sqrt(D)) / a, (-k - sqrt(D)) / a);
		}
	}
	else x = -c / (2 * k);

	return sf::Vector2f(x, 1/(2*d1) * (x - f1.x)*(x - f1.x) + (f1.y + y_d)/2);

}
std::pair<sf::Vector2f, sf::Vector2f> intersection(sf::Vector2f& f1, sf::Vector2f& f2, float y_d)
{
	float x1, x2;
	float d1 = f1.y - y_d;
	float d2 = f2.y - y_d;

	float a = 0.5f / d1 - 0.5f / d2,
		k = f2.x / (2 * d2) - f1.x / (2 * d1),
		c = f1.x*f1.x / (2 * d1) - f2.x*f2.x / (2 * d2) + 0.5f * (d1 - d2);
	
	if (a != 0) {
		float D = k * k - a * c;

		if (D < 0) throw std::logic_error("Discriminant < 0");
		x1 = (-k + sqrt(D)) / a;
		x2 = (-k - sqrt(D)) / a;
	}
	else { 
		x1 = -c / (2 * k);
		x2 = x1;
	};

	return { sf::Vector2f(x1, 1 / (2 * d1) * (x1 - f1.x)*(x1 - f1.x) + (f1.y + y_d) / 2) ,
		sf::Vector2f(x2, 1 / (2 * d1) * (x2 - f1.x)*(x2 - f1.x) + (f1.y + y_d) / 2) };

}

std::pair<sf::Vector2f, sf::Vector2f> directionsOfEdges(sf::Vector2f n)
{
	float length = std::sqrt(n.x*n.x + n.y*n.y);
	sf::Vector2f dir1(- n.y / length, n.x/length), dir2 = -dir1;;
	return {dir1, dir2};
}

std::pair<sf::Vector2f, sf::Vector2f> intersectionLineAndArc(Edge & e, Arc & arc)
{
	if (e.b != 0) {
		float k_e = -e.a / e.b;
		float b_e = -e.c / e.b;
		float D = (arc.b - k_e)*(arc.b - k_e) - 4 *arc.a* (arc.c - b_e);
		if (D < 0) throw std::logic_error("line doesn't intersect with parabola");
		float x1 = (k_e - arc.b + sqrt(D))/(2*arc.a), x2 = (k_e - arc.b - sqrt(D))/(2*arc.a);

		return { {x1, e.atX(x1)}, 
				 {x2, e.atX(x2)} };
	}
	else {
		//case when edge line is paralel to Y axis
		//then we have only one intersection
		sf::Vector2f intr (-e.c / e.a, arc.atX(-e.c / e.a));
		return {intr, intr};
	}
}

sf::Vector2f intersectionLines(Edge& e1, Edge& e2) {
	if ((e1.a == e2.a) && (e1.b == e2.b)) throw std::logic_error("lines are parallel");

	float x = (-e2.c / e2.b + e1.c / e1.b) / (-e1.a / e1.b + e2.a / e2.b);
	return { x, e1.atX(x) };
}

bool areParallel(Edge& e1, Edge& e2) {
	return ((e1.a == e2.a) && (e1.b == e2.b));
}

float dist(sf::Vector2f p1, sf::Vector2f p2) {
	return (float)sqrt(((p1 - p2).x)*((p1 - p2).x) + ((p1 - p2).y)*((p1 - p2).y));
}

float length(sf::Vector2f v) {
	return (float)(sqrt(v.x*v.x + v.y*v.y));
}


bool hasTheSameDirection(sf::Vector2f v, sf::Vector2f dir) {
	float eps = 0.001;
	return dist(v, dir) < length(v) + length(dir);
}