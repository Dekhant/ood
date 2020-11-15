#pragma once
#include "CommonTypes.h"
#include <functional>
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetFillColor(RGBAColor color) = 0;
	virtual void SetLineThickness(double thickness) = 0;

	virtual void DrawLine(PointD const& from, PointD const& to) = 0;
	virtual void FillPolygon(std::vector<PointD> const& vertexes) = 0;

	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	virtual void FillEllipse(double left, double top, double width, double height) = 0;

	virtual ~ICanvas() = default;
};