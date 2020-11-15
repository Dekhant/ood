#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle();

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	std::optional<double> GetThickness() const override;
	void SetThickness(double thickness) override;

private:
	bool m_isEnabled = true;
	RGBAColor m_color;
	double m_thickness;
};