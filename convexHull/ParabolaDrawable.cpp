#include "ParabolaDrawable.h"

Parabola::Parabola(float dir_y_init, sf::Vector2f & f_init, float x_left, float x_right): dir_y(dir_y_init), f(f_init)
{
	init(x_left, x_right);
}

void Parabola::setColor(sf::Color& color) noexcept
{
	parabolaColor = color;
}

void Parabola::init(float x_left, float x_right)
{
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

float Parabola::atX(float x) const noexcept
{
	return 1/(2 * (f.y - dir_y)) * (x - f.x)*(x - f.x) + (f.y + dir_y)/2;
}


void Parabola::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &m_texture;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(arr, states);
}

void PointD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	sf::RectangleShape rect(sf::Vector2f(pointSize, pointSize));
	rect.setFillColor(pointColor);
	rect.setPosition(p - sf::Vector2f(pointSize/2, pointSize / 2));
	target.draw(rect);
}

PointD::PointD(float x, float y)
{
	p.x = x;
	p.y = y;
}

PointD::PointD(sf::Vector2f v): p(v){}

void PointD::setColor(sf::Color newColor)
{
	pointColor = newColor;
}


