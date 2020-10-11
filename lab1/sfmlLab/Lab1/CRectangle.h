#pragma once
#include "CBody.h"
#include <SFML/Graphics.hpp>

class CRectangle: public CBody
{
public:
	sf::Shape* m_rectangle;

	CRectangle(sf::Shape* rectangle) : m_rectangle(rectangle)
	{
	}

	float GetArea() override
	{
		return static_cast<sf::RectangleShape*>(m_rectangle)->getSize().x * static_cast<sf::RectangleShape*>(m_rectangle)->getSize().y;
	}

	float GetPerimeter() override
	{
		return static_cast<sf::RectangleShape*>(m_rectangle)->getSize().x * 2 + static_cast<sf::RectangleShape*>(m_rectangle)->getSize().y * 2;
	}
};