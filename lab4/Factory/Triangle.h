#pragma once
#include "Shape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, Point const& vertex1, Point const& vertex2, Point const& vertex3);

	void Draw(ICanvas& canvas) const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};