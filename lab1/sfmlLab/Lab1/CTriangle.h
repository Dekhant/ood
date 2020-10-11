#pragma once
#include "CBody.h"
#include <SFML/Graphics.hpp>

class CTriangle: public CBody
{
public:
	sf::Shape* m_triangle;

	CTriangle(sf::Shape* triangle) : m_triangle(triangle)
	{
	}

	float GetArea() override
	{
		sf::ConvexShape* triangle = static_cast<sf::ConvexShape*>(m_triangle);
		sf::Vector2f a = triangle->getPoint(0);
		sf::Vector2f b = triangle->getPoint(1);
		sf::Vector2f c = triangle->getPoint(2);
		float side1 = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
		float side2 = sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2));
		float side3 = sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2));
		float halfPerimeter = (side1 + side2 + side3) / 2;
		return sqrt(halfPerimeter * (halfPerimeter - side1) * (halfPerimeter - side2) * (halfPerimeter - side3));
	}

	float GetPerimeter() override
	{
		sf::ConvexShape* triangle = static_cast<sf::ConvexShape*>(m_triangle);
		sf::Vector2f a = triangle->getPoint(0);
		sf::Vector2f b = triangle->getPoint(1);
		sf::Vector2f c = triangle->getPoint(2);
		float ab = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
		float ac = sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2));
		float bc = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));
		return ab + ac + bc;
	}
};