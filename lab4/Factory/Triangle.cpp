#include "Triangle.h"

CTriangle::CTriangle(Color color, Point const& vertex1, Point const& vertex2, Point const& vertex3)
	: CShape(color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex1, m_vertex3);
	canvas.DrawLine(m_vertex2, m_vertex3);
}

Point CTriangle::GetVertex1() const
{
	return m_vertex1;
}

Point CTriangle::GetVertex2() const
{
	return m_vertex2;
}

Point CTriangle::GetVertex3() const
{
	return m_vertex3;
}