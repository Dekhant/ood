#include "FillStyle.h"

CFillStyle::CFillStyle()
	: m_color(0)
{
}

std::optional<bool> CFillStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CFillStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

std::optional<RGBAColor> CFillStyle::GetColor() const
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}
