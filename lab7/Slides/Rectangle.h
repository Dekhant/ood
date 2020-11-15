#pragma once
#include "SimpleShape.h"

class CRectangle : public CSimpleShape
{
public:
	CRectangle(PointD const& leftTop, double width, double height);

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	void DrawingBehavior(ICanvas& canvas) const override;

private:
	PointD m_leftTop;
	double m_width;
	double m_height;
};