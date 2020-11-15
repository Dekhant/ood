#pragma once
#include "SimpleShape.h"

class CEllipse : public CSimpleShape
{
public:
	CEllipse(PointD const& center, double horizontalRadius, double verticalRadius);

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	void DrawingBehavior(ICanvas& canvas) const override;

private:
	PointD m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};