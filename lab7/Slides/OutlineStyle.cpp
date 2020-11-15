#include "OutlineStyle.h"

COutlineStyle::COutlineStyle()
	: m_color(0)
	, m_thickness(1)
{
}

std::optional<bool> COutlineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void COutlineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

std::optional<RGBAColor> COutlineStyle::GetColor() const
{
	return m_color;
}

void COutlineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

std::optional<double> COutlineStyle::GetThickness() const
{
	return m_thickness;
}

void COutlineStyle::SetThickness(double thickness)
{
	m_thickness = thickness;
}