#include "RegularPolygon.h"
#include <stdexcept>

CRegularPolygon::CRegularPolygon(Color color, size_t vertexCount, Point const& center, double radius)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
{
	if (vertexCount < 3)
	{
		throw std::invalid_argument("Vertex count must be more than 2");
	}
	m_vertexCount = vertexCount;
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);

	std::vector<Point> vertexes = GetVertexes();

	for (size_t i = 0; i < m_vertexCount - 1; i++)
	{
		canvas.DrawLine(vertexes[i], vertexes[i + 1]);
	}

	Point firstVertex = vertexes[0];
	Point lastVertex = vertexes[m_vertexCount - 1];
	canvas.DrawLine(lastVertex, firstVertex);
}

const double PI = 3.1416;

std::vector<Point> CRegularPolygon::GetVertexes() const
{
	std::vector<Point> vertexes;
	double offsetAngle = 2 * PI / m_vertexCount;

	for (size_t i = 0; i < m_vertexCount; i++)
	{
		vertexes.push_back({
			m_center.x + m_radius * cos(offsetAngle * i),
			m_center.y + m_radius * sin(offsetAngle * i),
			});
	}

	return vertexes;
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

Point CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}