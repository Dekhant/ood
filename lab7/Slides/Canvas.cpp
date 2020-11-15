#include "Canvas.h"

CCanvas::CCanvas(sf::RenderTarget& renderTarget)
	: m_renderTarget(renderTarget)
	, m_lineThickness(0)
{
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = sf::Color(color);
}

void CCanvas::SetFillColor(RGBAColor color)
{
	m_fillColor = sf::Color(color);
}

void CCanvas::SetLineThickness(double thickness)
{
	m_lineThickness = (float)thickness;
}

void CCanvas::DrawLine(PointD const& from, PointD const& to)
{
	sf::Vertex vertices[4];
	sf::Vector2f point1(float(from.x), float(from.y));
	sf::Vector2f point2(float(to.x), float(to.y));

	sf::Vector2f direction = point2 - point1;
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (m_lineThickness / 2.f) * unitPerpendicular;

	vertices[0].position = point1 + offset;
	vertices[1].position = point2 + offset;
	vertices[2].position = point2 - offset;
	vertices[3].position = point1 - offset;

	for (int i = 0; i < 4; ++i)
	{
		vertices[i].color = m_lineColor;
	}

	m_renderTarget.draw(vertices, 4, sf::Quads);
}

void CCanvas::FillPolygon(std::vector<PointD> const& vertexes)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexes.size());

	for (size_t i = 0; i < vertexes.size(); i++)
	{
		sf::Vector2f point = { float(vertexes[i].x), float(vertexes[i].y) };
		polygon.setPoint(i, point);
	}

	polygon.setFillColor(m_fillColor);
	polygon.setOutlineColor(sf::Color(0, 0, 0, 0));

	m_renderTarget.draw(polygon);
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	sf::Vector2f center = { float(left + width / 2), float(top + height / 2) };
	float horizontalRadius = (float)width / 2;
	float verticalRadius = (float)height / 2;

	sf::CircleShape circle(horizontalRadius);
	circle.setOrigin(horizontalRadius, horizontalRadius);
	circle.move(center);
	circle.setScale(1.f, verticalRadius / horizontalRadius);

	circle.setOutlineColor(m_lineColor);
	circle.setOutlineThickness(m_lineThickness);
	circle.setFillColor(sf::Color(0, 0, 0, 0));

	m_renderTarget.draw(circle);
}

void CCanvas::FillEllipse(double left, double top, double width, double height)
{
	sf::Vector2f center = { float(left + width / 2), float(top + height / 2) };
	float horizontalRadius = (float)width / 2;
	float verticalRadius = (float)height / 2;

	sf::CircleShape circle(horizontalRadius);
	circle.setOrigin(horizontalRadius, horizontalRadius);
	circle.move(center);
	circle.setScale(1.f, verticalRadius / horizontalRadius);

	circle.setOutlineColor(sf::Color(0, 0, 0, 0));
	circle.setFillColor(m_fillColor);

	m_renderTarget.draw(circle);
}