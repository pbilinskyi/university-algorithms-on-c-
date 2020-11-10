#include "Event.h"


Event::Event(sf::Vector2f p): point(p), y_d(p.y){
	type = EventType::SITE_EVENT;
}

Event::Event(float y_d1, sf::Vector2f p, int key_init) : point(p), key(key_init), y_d(y_d1) {
	type = EventType::EDGE_INTERSECTION_EVENT;
}


bool Event::operator<(const Event& other) const {

	if (this->y_d != other.y_d) 
		return this->y_d > other.y_d;
	else 
		return this->point.x > other.point.x;
}

bool Event::operator==(const Event& other) const {
	return ((y_d == other.y_d)&&(point == other.point));
}

int Event::getKeyOfArc() const
{
	return key;
}

/*
Event::Event(EventType t, sf::Vector2f p): point(p), type(t){}

SiteEvent::SiteEvent(EventType t, sf::Vector2f s): Event(t, s){}

EdgeIntrEvent::EdgeIntrEvent(EventType t, sf::Vector2f p, float x) : Event(t, p), arc_x_left(x) {}
*/