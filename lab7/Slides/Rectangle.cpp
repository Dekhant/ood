#include "Rectangle.h"

CRectangle::CRectangle(PointD const& leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

std::optional<RectD> CRectangle::GetFrame() const
{
	return RectD{ m_leftTop, m_width, m_height };
}

void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTop = rect.leftTop;
	m_width = rect.width;
	m_height = rect.height;
}

void CRectangle::DrawingBehavior(ICanvas& canvas) const
{
	PointD rightBottom{ m_leftTop.x + m_width, m_leftTop.y + m_height };
	PointD rightTop{ rightBottom.x, m_leftTop.y };
	PointD leftBottom{ m_leftTop.x, rightBottom.y };

	if (*GetOutlineStyle()->IsEnabled())
	{
		canvas.DrawLine(m_leftTop, rightTop);
		canvas.DrawLine(rightTop, rightBottom);
		canvas.DrawLine(rightBottom, leftBottom);
		canvas.DrawLine(leftBottom, m_leftTop);
	}

	if (*GetFillStyle()->IsEnabled())
	{
		canvas.FillPolygon(std::vector<PointD>{ m_leftTop, rightTop, rightBottom, leftBottom });
	}
}
