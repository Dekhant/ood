#include "Ellipse.h"

CEllipse::CEllipse(PointD const& center, double horizontalRadius, double verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

std::optional<RectD> CEllipse::GetFrame() const
{
	PointD leftTop = { m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius };
	return RectD{ leftTop, m_horizontalRadius * 2, m_verticalRadius * 2 };
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_center = { rect.leftTop.x + rect.width / 2, rect.leftTop.y + rect.height / 2 };
	m_horizontalRadius = rect.width / 2;
	m_verticalRadius = rect.height / 2;
}

void CEllipse::DrawingBehavior(ICanvas& canvas) const
{
	PointD leftTop = { m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius };
	double width = 2 * m_horizontalRadius;
	double height = 2 * m_verticalRadius;

	if (*GetOutlineStyle()->IsEnabled())
	{
		canvas.DrawEllipse(leftTop.x, leftTop.y, width, height);
	}

	if (*GetFillStyle()->IsEnabled())
	{
		canvas.FillEllipse(leftTop.x, leftTop.y, width, height);
	}
}