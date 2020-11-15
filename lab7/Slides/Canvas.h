#pragma once
#include "ICanvas.h"
#include "SFML/Graphics.hpp"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& renderTarget);

	void SetLineColor(RGBAColor color) override;
	void SetFillColor(RGBAColor color) override;
	void SetLineThickness(double thickness) override;

	void DrawLine(PointD const& from, PointD const& to) override;
	void FillPolygon(std::vector<PointD> const& vertexes) override;

	void DrawEllipse(double left, double top, double width, double height) override;
	void FillEllipse(double left, double top, double width, double height) override;

private:
	sf::RenderTarget& m_renderTarget;

	sf::Color m_lineColor = sf::Color(0);
	sf::Color m_fillColor = sf::Color(0);
	float m_lineThickness = 0.;
};