#pragma once
#include <SFML/Graphics.hpp>
#include "ParabolaDrawable.h"
#include <ostream>
#include <utility>


class Edge: public sf::Drawable, public sf::Transformable {
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Edge() = default;
	Edge(sf::Vector2f origin, sf::Vector2f normal, sf::Vector2f dir);
	Edge operator-() const;

	void moveTo(sf::Vector2f);
	void scale(float scalar);
	float atX(float x);
	void init();

	sf::Vector2f origin;
	sf::Vector2f dir;
	sf::Vector2f P;
	float a=0, b=0, c=0;

	//for drawing
	sf::Vertex line[2];
	static sf::Color lineColor;
};


class Arc :public sf::Drawable, public sf::Transformable {
	int key;
public:
	sf::Vector2f f;
	float a, b, c;
	float y_d;
	bool wasChecked = false;

	//we should free memory when deleting an edge from beachline
	Edge *left = nullptr, *right = nullptr;

	Arc(sf::Vector2f& focus, float y_d, Edge* left, Edge* right, int key);
	friend std::ostream& operator<<(std::ostream& os, const Arc&);

	
	//for drawind
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void modify(float y_d) noexcept;
	int getKey() const noexcept;

	void init();
	float atX(float) const noexcept;
	void setColor(sf::Color&) noexcept;

	sf::Color parabolaColor = sf::Color::Green;
	static const size_t countApprLines = 100;
	sf::VertexArray arr;
};


sf::Vector2f intersection(sf::Vector2f& f1, sf::Vector2f& f2, float y_d, bool returnGreatest);

std::pair<sf::Vector2f, sf::Vector2f> intersection(sf::Vector2f& f1, sf::Vector2f& f2, float y_d);

std::pair<sf::Vector2f, sf::Vector2f> directionsOfEdges(sf::Vector2f normal);

std::pair<sf::Vector2f, sf::Vector2f> intersectionLineAndArc(Edge& e, Arc& a);

sf::Vector2f intersectionLines(Edge& e1, Edge& e2);

bool areParallel(Edge& e1, Edge& e2);

float dist(sf::Vector2f p1, sf::Vector2f p2);

float length(sf::Vector2f v);

bool hasTheSameDirection(sf::Vector2f v, sf::Vector2f dir);