#pragma once
#include "SimpleShape.h"

class CTriangle : public CSimpleShape
{
public:
	CTriangle(PointD const& vertex1, PointD const& vertex2, PointD const& vertex3);

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;
	void DrawingBehavior(ICanvas& canvas) const override;

private:
	PointD m_vertex1;
	PointD m_vertex2;
	PointD m_vertex3;
};