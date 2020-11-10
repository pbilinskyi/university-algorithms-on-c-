//source/repos/"3d Term"/VoronoiDiagram
#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>

#include <algorithm>
#include <iterator>
#include <list>
#include <queue>

#include "Arc.h"
#include "Event.h"
#include "SFML/Graphics.hpp"



using namespace std;

priority_queue<Event> eventQueue;
const float windowSize = 500;
int nextKey = 1;

float dotProduct(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

bool haveTheSameDirection(sf::Vector2f v1, sf::Vector2f v2) {
	return dotProduct(v1, v2) > 0;
}

bool isSqueezing(list<Arc>::iterator it) {
	sf::Vector2f intrs = intersectionLines(*it->left, *it->right);
	return haveTheSameDirection(intrs - it->left->origin, it->left->dir);
}

void addIntersectionEvent(list<Arc>::iterator it) {
	sf::Vector2f intrs = intersectionLines(*it->left, *it->right);
	eventQueue.push(Event(intrs.y + dist(it->f, intrs), intrs, it->getKey()));
}

//assume that focus lies on directrix

//cannot properly modify edges in case where initial sites has equal y coordinates
void insertToBeachline(list<Arc>& beachline, sf::Vector2f focus, float y_d) {
	float x = focus.x;
	list<Arc>::iterator it = beachline.begin();
	while ((it != beachline.end()) && (it->right->P.x <= x)) ++it;

	if (it != beachline.end()) {
		sf::Vector2f normal = focus - it->f;
		sf::Vector2f origin(focus.x, it->atX(focus.x));

		std::pair<sf::Vector2f, sf::Vector2f> directions = directionsOfEdges(normal);
		sf::Vector2f dir_left, dir_right;
		if (directions.first.x <= 0) {
			dir_left = directions.first;
			dir_right = directions.second;
		}
		else {
			dir_left = directions.second,
			dir_right = directions.first;
		}
		Edge *e_l = new Edge(origin, normal, dir_left),
			*e_r = new Edge(origin, normal, dir_right);

		Arc rightSplitted(it->f, y_d, e_r, it->right, nextKey++);
		it->right = e_l;
		Arc newArc(focus, y_d, e_l, e_r, nextKey++);
		++it;
		beachline.insert(it, newArc);
		beachline.insert(it, rightSplitted);

		//CHECK intersections for left and right arcs
		--it;	//rightSplitted
		if (isSqueezing(it)) {
			cout << *it << endl;
			addIntersectionEvent(it);
		}
		--it;	//newArc - won't be squeezed at this stage, because it's focus has the biggest y coordinate among all of arcs in beachline
		--it;	//previous between newArc - always exist, so we can dereferense it
		if (isSqueezing(it)) {
			cout << *it << endl;
			addIntersectionEvent(it);
		}
	}
	else {
			float bigNegativeNumber = -windowSize*10;
			Edge* e_l = new Edge(sf::Vector2f(focus.x, bigNegativeNumber), sf::Vector2f(0, 1), sf::Vector2f(-1, 0)),
				*e_r = new Edge(sf::Vector2f(focus.x, bigNegativeNumber), sf::Vector2f(0, 1), sf::Vector2f(1, 0));
			beachline.insert(it, Arc(focus, y_d, e_l, e_r, nextKey++));
	}
}



void drawBeachline(list<Arc>& lst, sf::RenderTarget& target) {
	for_each(lst.begin(), lst.end(), [&target](Arc& arc) {
		arc.init();
		target.draw(arc);
		arc.left->init();
		target.draw(*(arc.left));
	});
	
}

void drawDirectrix(float y_d, sf::RenderTarget& target) {
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(0.f, y_d)),
		sf::Vertex(sf::Vector2f(windowSize, y_d))
	};

	target.draw(line, 2, sf::Lines);
}

void drawSites(list<Point>& lst, sf::RenderTarget& target) {
	for (list<Point>::iterator it = lst.begin(); it != lst.end(); ++it) {
		target.draw(*it);
	}
}

void modifyBeachline(list<Arc>& beachline, float y_d) {
	list<Arc>::iterator it = beachline.begin();
	if ((it != beachline.end()) && (it->right->P.x < 0))  {
			cout << *it << " - deleted, too far left" << endl;
			delete it->left;
			it = beachline.erase(it);
	}

	for (list<Arc>::iterator it = beachline.begin(); it != beachline.end(); ++it) {
		it->modify(y_d);
	
		std::pair<sf::Vector2f, sf::Vector2f> intrs_left = intersectionLineAndArc(*(it->left), *it);
		std::pair<sf::Vector2f, sf::Vector2f> intrs_right = intersectionLineAndArc(*(it->right), *it);
		sf::Vector2f P_left, P_right;

		if (haveTheSameDirection(intrs_left.first - it->left->origin, it->left->dir)) {
			P_left = intrs_left.first;
		}
		else {
			P_left = intrs_left.second;
		}

		if (haveTheSameDirection(intrs_right.first - it->right->origin, it->right->dir)) {
			P_right = intrs_right.first;
		}
		else {
			P_right = intrs_right.second;
		}

		//move edge ends to new intersection points
		it->left->moveTo(P_left);
		it->right->moveTo(P_right);
	}
	if (it != beachline.begin()) {
		--it;
		if ((it->left->P.x > windowSize)) {
			cout << *it << " - deleted, too far right" << endl;
			delete it->right;
			it = beachline.erase(it);

		}
	}
}

void squeeze(sf::VertexArray& diagramPicture, list<Arc>& beachline, int key, sf::Vector2f intrs, float y_d_then) {
		//there will be a problem: if the element you added to queue, is not already in the container, 
		//iterator is not dereferencable
		//chose the other way to identify arc to remove rather then using iterators
	list<Arc>::iterator it = beachline.begin();
	while ((it != beachline.end()) && (it->getKey() != key))  ++it;

	if (it != beachline.end())	{
		it->left->moveTo(intrs);
		it->right->moveTo(intrs);
		//diagramPicture.resize(diagramPicture.getVertexCount() + 4);
		diagramPicture.append(it->left->line[0]);
		diagramPicture.append(it->left->line[1]);
		diagramPicture.append(it->right->line[0]);
		diagramPicture.append(it->right->line[1]);
		//next after erased element
		delete it->left;
		delete it->right;
		it = beachline.erase(it);

		sf::Vector2f f1;
		f1 = it->f;
		--it;
		sf::Vector2f f2 = it->f;
		sf::Vector2f dir;
		std::pair<sf::Vector2f, sf::Vector2f> dirs = directionsOfEdges(f1 - f2);
		dir = dirs.first.y > 0 ? dirs.first : dirs.second;

		Edge* e = new Edge(intrs, f1 - f2, dir);
		it->right = e;
		it->modify(y_d_then);
		++it;
		it->left = e;
		it->modify(y_d_then);
	}
}


int main() {

	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "SFML works!");
	sf::VertexArray diagramPicture;
	diagramPicture.setPrimitiveType(sf::Lines);
	list<Point> sites;
	
	ifstream ifs("data.txt");
	if (!ifs) cout << "Input error: opening failed" << endl;
	size_t coordQuadSize;
	ifs >> coordQuadSize;
	float x, y;
	while (ifs >> x >> y) {
		sf::Vector2f p(x / coordQuadSize * windowSize, y / coordQuadSize * windowSize);
		eventQueue.push(Event(p));
		sites.push_back(Point(p));
	}
	if (!ifs.eof())  cout << "Output error: reading failed" << endl;
	ifs.close();
/*
	for (size_t i = 1; i <= 10; ++i) {
		sf::Vector2f p = sf::Vector2f(float(rand() % int(windowSize)), (rand() % int(windowSize)));
		eventQueue.push(Event(p));
		sites.push_back(Point(p));
	}
*/

	float y_d;
	list<Arc> beachline;
	while (!eventQueue.empty())
	{
		window.clear();
		Event ev = eventQueue.top();
		eventQueue.pop();
		if (ev.type == EventType::SITE_EVENT) {
			y_d = ev.y_d;
			modifyBeachline(beachline, y_d);
			insertToBeachline(beachline, ev.point, y_d);
			drawBeachline(beachline, window);
		}
		else if ((ev.type == EventType::EDGE_INTERSECTION_EVENT) &&(ev.y_d>= y_d) && (ev.point.x <= windowSize)){
			y_d = ev.y_d;
			modifyBeachline(beachline, y_d);
			squeeze(diagramPicture, beachline, ev.getKeyOfArc(), ev.point, y_d);
			drawBeachline(beachline, window);
		}
		window.draw(diagramPicture);
		drawDirectrix(y_d, window);
		drawSites(sites, window);
		window.display();
	}

	window.clear();
	modifyBeachline(beachline, windowSize*10);
	drawBeachline(beachline, window);
	drawSites(sites, window);
	window.draw(diagramPicture);
	window.display();

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asMilliseconds() >= 1000) {
			
		}

		//window.clear();
		//drawBeachline(beachline, window);
		//drawDirectrix(y_d, window);
		//window.display();
	}
	
	
	system("pause");
	return 0;
}