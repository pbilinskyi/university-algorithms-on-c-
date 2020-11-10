#pragma once

#include "Arc.h"
#include <list>


enum EventType{	SITE_EVENT, EDGE_INTERSECTION_EVENT};

class Event {
	int key;
public:
	Event(sf::Vector2f);
	Event(float y_d, sf::Vector2f intr, int key);

	bool operator<(const Event&) const;
	bool operator==(const Event&) const;

	sf::Vector2f point;
	float y_d = 0;
	EventType type;
	
	//supposed to be used only for edge intersection events
	int getKeyOfArc() const;
};

/*class SiteEvent : public Event {
public:
	SiteEvent(EventType, sf::Vector2f);
};

class EdgeIntrEvent: public Event {
public:
	EdgeIntrEvent(sf::Vector2f, float);
	float arc_x_left;
};
*/