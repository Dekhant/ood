#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, Point const& leftTop, double width, double height);

	void Draw(ICanvas& canvas) const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;
private:
	Point m_leftTop;
	double m_width;
	double m_height;
};