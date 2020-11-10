#pragma once
#include "SFML/Graphics.hpp"

class Parabola : public sf::Drawable, public sf::Transformable
{
public:
	Parabola(float directrics_y, sf::Vector2f& focus, float x_left, float x_right);
	void setColor(sf::Color&) noexcept;

private:
	//inherited form sf::Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//
	void init(float x_left, float x_right);
	float atX(float) const noexcept;


	static const size_t countApprLines = 100;
	float dir_y;
	sf::Vector2f f;
	
	sf::Color parabolaColor = sf::Color::Green;
	sf::VertexArray arr;
	sf::Texture m_texture;
};

class PointD:  public sf::Drawable, public sf::Transformable{
private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Color pointColor = sf::Color::Red;
		float pointSize = 5;
		sf::Vector2f p;
public:
	PointD(float x, float y);
	PointD(sf::Vector2f);

	void setColor(sf::Color);
};