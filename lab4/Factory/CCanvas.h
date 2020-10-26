#pragma once
#include "ICanvas.h"
#include "Color.h"
#include "SFML/Graphics.hpp"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& renderTarget);
	void SetColor(Color color) override;
	void DrawLine(Point const& from, Point const& to);
	void DrawEllipse(Point const& center, double verticalRadius, double horizontalRadius);

private:
	sf::Vector2f GetCoordOnCanvas(Point const& point);
	sf::RenderTarget& m_renderTarget;
	int m_width;
	int m_height;
	sf::Color m_color;
};