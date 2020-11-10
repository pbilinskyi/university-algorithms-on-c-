//source/repos/"3d Term"/convexHull

#include "geometryBasic.h"
#include "ParabolaDrawable.h"
#include <iostream>
#include <fstream>
#include <list>
#include "SFML/Graphics.hpp"

const float windowSide = 800;


using namespace std;

void print_list(list<Point> lst) {

	for (auto it = lst.begin(); it != lst.end(); ++it) {
		cout <<*it << " -> ";
	}
}

void move_origin_transform(list<Point>& lst, const Point new_origin) {
	for (auto it = lst.begin(); it != lst.end(); ++it) {		
		*it = *it - new_origin;
	}
}

void init(const char* fname, list<Point>& lst) {

	ifstream ifs("data.txt");
	Point left_border(0, 0);
	Point P(0, 0);
	ifs >> left_border.x >> left_border.y;

	while (ifs >> P.x >> P.y) {
		if ((P.y < left_border.y) || ((P.y == left_border.y) && (P.x < left_border.x))) {
			lst.push_back(left_border);
			left_border.x = P.x;
			left_border.y = P.y;
		}
		else 
		lst.push_back(P);
	}

	lst.push_front(left_border);
	

	if (!ifs && !ifs.eof()) cout << "Err: I/O error occured." << endl;

}

list<Point> GrahamsScan(list<Point>& P) {
	Point origin = *(P.begin());
	move_origin_transform(P, origin);
	P.sort();
	//print_list(P);
	size_t N = P.size();
	list<Point> lst;

	if (N <= 3) return P;
	else {
		auto it = P.begin();
		lst.push_front(*it++);
		lst.push_front(*it++);
		lst.push_front(*it++);
		for (; it != P.end(); ++it) {
			
			while (det(*(++(lst.begin())), *lst.begin(), *it) > 0) {
				lst.pop_front();
			}
				

			lst.push_front(*it);
		}
	}
	move_origin_transform(lst, origin * -1);

	return lst;

}

void listToPolygon(const list<Point>& lst, sf::ConvexShape& shape) {
	shape.setPointCount(lst.size());
	size_t i = 0;
	shape.setOrigin(0, 0);
	for (auto it = lst.begin(); it != lst.end(); ++it, ++i) {
		shape.setPoint(i, sf::Vector2f(static_cast<float>(it->x)*windowSide/20, static_cast<float>(it->y)*windowSide/20));
	}
}

void listToVertexArray(const list<Point>& lst, sf::VertexArray& arr) {
	size_t i = 0;
	for (auto it = lst.begin(); it != lst.end(); ++it, ++i) {
		arr[i] = sf::Vector2f(static_cast<float>(it->x)*windowSide / 20, static_cast<float>(it->y)*windowSide / 20);
		//shape.setPoint(i, sf::Vector2f(static_cast<float>(it->x)*windowSide / 20, static_cast<float>(it->y)*windowSide / 20));
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSide, windowSide), "SFML works!");
	sf::ConvexShape shape;

	list<Point> lst, convexHull;
	init("data.txt", lst);
	convexHull = GrahamsScan(lst);
	listToPolygon(convexHull, shape);

	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1);
	shape.setOrigin(-windowSide / 2.f, -windowSide / 2.f);
	sf::Vertex ox[] = { sf::Vertex({windowSide / 2.f, 0.f}), sf::Vertex({windowSide / 2.f, windowSide}) };
	sf::Vertex oy[] = { sf::Vertex({0.f, windowSide / 2.f}), sf::Vertex({windowSide, windowSide / 2.f}) };

	

	window.draw(shape);
	for (auto it = lst.begin(); it != lst.end(); ++it) {

		sf::RectangleShape rect(sf::Vector2f(5, 5));
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(sf::Vector2f (float(it->x) * windowSide/20.f, float(it->y) * windowSide/20.f) - sf::Vector2f(5.f / 2.f, 5.f / 2.f));
		rect.setOrigin(-windowSide / 2.f - windowSide / 20.f, -windowSide / 2.f - windowSide / 20.f);
		window.draw(rect);
	}
	window.draw(ox, 2, sf::Lines);
	window.draw(oy, 2, sf::Lines);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//window.clear();
		//window.draw(shape);
		//window.display();
	}

	system("pause");
	return 0;
}