#include "CCanvas.h"


CCanvas::CCanvas(sf::RenderTarget& renderTarget)
	: m_renderTarget(renderTarget)
{
	m_height = renderTarget.getSize().x;
	m_width = renderTarget.getSize().y;
}

void CCanvas::SetColor(Color color)
{
	if (color == Color::Black)
	{
		m_color = sf::Color::Black;
	}
	else if (color == Color::Blue)
	{
		m_color = sf::Color::Blue;
	}
	else if (color == Color::Green)
	{
		m_color = sf::Color::Green;
	}
	else if (color == Color::Pink)
	{
		m_color = sf::Color(255, 192, 203);
	}
	else if (color == Color::Red)
	{
		m_color = sf::Color::Red;
	}
	else if (color == Color::Yellow)
	{
		m_color = sf::Color::Yellow;
	}
}

void CCanvas::DrawLine(Point const& from, Point const& to)
{
	sf::Vertex line[] = {
		sf::Vertex(GetCoordOnCanvas(from)),
		sf::Vertex(GetCoordOnCanvas(to))
	};
	line[0].color = m_color;
	line[1].color = m_color;
	m_renderTarget.draw(line, 2, sf::Lines);
}

void CCanvas::DrawEllipse(Point const& center, double verticalRadius, double horizontalRadius)
{
	sf::CircleShape circle((float)horizontalRadius);
	circle.setOrigin((float)horizontalRadius, (float)horizontalRadius);
	circle.move(GetCoordOnCanvas(center));
	circle.setScale(float(verticalRadius / horizontalRadius), 1.f);

	circle.setOutlineColor(m_color);
	circle.setOutlineThickness(3.f);
	circle.setFillColor(sf::Color(0, 0, 0, 0));

	m_renderTarget.draw(circle);
}

sf::Vector2f CCanvas::GetCoordOnCanvas(Point const& point)
{
	return sf::Vector2f((float)point.x, m_height - (float)point.y);
}