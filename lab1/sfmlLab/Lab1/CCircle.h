#pragma once
#include "CBody.h"
#include <SFML/Graphics.hpp>

const float P = 3.14f;

class CCircle: public CBody
{
public:
	sf::Shape* m_circle;
	CCircle(sf::Shape* circle) : m_circle(circle)
	{
	}
	float GetArea() override
	{
		return pow(static_cast<sf::CircleShape*>(m_circle)->getRadius(), 2) * P;
	}
	float GetPerimeter() override
	{
		return static_cast<sf::CircleShape*>(m_circle)->getRadius() * 2 * P;
	}
};