#include "Triangle.h"
#include <algorithm>

CTriangle::CTriangle(PointD const& vertex1, PointD const& vertex2, PointD const& vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

std::optional<RectD> CTriangle::GetFrame() const
{
	double minX = std::min({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double minY = std::min({ m_vertex1.y, m_vertex2.y, m_vertex3.y });
	double maxX = std::max({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double maxY = std::max({ m_vertex1.y, m_vertex2.y, m_vertex3.y });

	return RectD{ { minX, minY }, maxX - minX, maxY - minY };
}

void CTriangle::SetFrame(const RectD& rect)
{
	RectD currentFrame = *GetFrame();

	std::function<void(PointD&)> updateVertex = [&](PointD& vertex) {
		vertex.x = rect.leftTop.x + (vertex.x - currentFrame.leftTop.x) / currentFrame.width * rect.width;
		vertex.y = rect.leftTop.y + (vertex.y - currentFrame.leftTop.y) / currentFrame.height * rect.height;
	};

	updateVertex(m_vertex1);
	updateVertex(m_vertex2);
	updateVertex(m_vertex3);
}

void CTriangle::DrawingBehavior(ICanvas& canvas) const
{
	if (*GetOutlineStyle()->IsEnabled())
	{
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

	if (*GetFillStyle()->IsEnabled())
	{
		canvas.FillPolygon(std::vector<PointD>{ m_vertex1, m_vertex2, m_vertex3 });
	}
}