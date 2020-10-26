#pragma once
#include "Color.h"
#include "Point.h"


class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point const& from, Point const& to) = 0;
	virtual void DrawEllipse(Point const& center, double verticalRadius, double horizontalRadius) = 0;

	virtual ~ICanvas() = default;
};