#include "Rectangle.h"

CRectangle::CRectangle(Color color, Point const& leftTop, double width, double height)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	Point rightBottom = GetRightBottom();
	Point leftBottom{ m_leftTop.x, rightBottom.y };
	Point rightTop{ rightBottom.x, m_leftTop.y };

	canvas.SetColor(m_color);
	canvas.DrawLine(m_leftTop, leftBottom);
	canvas.DrawLine(leftBottom, rightBottom);
	canvas.DrawLine(rightBottom, rightTop);
	canvas.DrawLine(rightTop, m_leftTop);
}

Point CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point CRectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y - m_height };
}