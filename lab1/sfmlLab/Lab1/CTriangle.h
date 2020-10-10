#pragma once
#include "CBody.h"
#include <SFML/Graphics.hpp>

class CRectangle final : public CBody
{
public:
	sf::Shape* m_rectangle;

	CRectangle(sf::Shape* triangle) : m_rectangle(triangle)
	{
	}

	float GetArea() override
	{
		sf::ConvexShape* triangle = static_cast<sf::ConvexShape*>(m_rectangle);
		sf::Vector2f a = triangle->getPoint(0);
		sf::Vector2f b = triangle->getPoint(1);
		sf::Vector2f c = triangle->getPoint(2);
		return 0.5f * fabs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
	}

	float GetPerimeter() override
	{
		sf::ConvexShape* triangle = static_cast<sf::ConvexShape*>(m_rectangle);
		sf::Vector2f a = triangle->getPoint(0);
		sf::Vector2f b = triangle->getPoint(1);
		sf::Vector2f c = triangle->getPoint(2);
		float ab = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
		float ac = sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2));
		float bc = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));
		return ab + ac + bc;
	}
};