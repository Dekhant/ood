#include "GroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(OutlineStyleEnumerator enumerator)
	: m_enumerator(enumerator)
{
}

std::optional<bool> CGroupOutlineStyle::IsEnabled() const
{
	std::optional<bool> isEnabled = std::nullopt;
	bool isInit = false;

	OutlineStyleCallback callback = [&](IOutlineStyle& style) {
		if (!isInit)
		{
			isEnabled = style.IsEnabled();
			isInit = true;
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = std::nullopt;
		}
	};

	m_enumerator(callback);

	return isEnabled;
}

void CGroupOutlineStyle::Enable(bool enable)
{
	OutlineStyleCallback callback = [&](IOutlineStyle& style) {
		style.Enable(enable);
	};

	m_enumerator(callback);
}

std::optional<RGBAColor> CGroupOutlineStyle::GetColor() const
{
	std::optional<RGBAColor> color = std::nullopt;
	bool isInit = false;

	OutlineStyleCallback callback = [&](IOutlineStyle& style) {
		if (!isInit)
		{
			color = style.GetColor();
			isInit = true;
		}
		else if (color != style.GetColor())
		{
			color = std::nullopt;
		}
	};

	m_enumerator(callback);

	return color;
}

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	OutlineStyleCallback callback = [&](IOutlineStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(callback);
}

std::optional<double> CGroupOutlineStyle::GetThickness() const
{
	std::optional<double> thickness = std::nullopt;
	bool isInit = false;

	OutlineStyleCallback callback = [&](IOutlineStyle& style) {
		if (!isInit)
		{
			thickness = style.GetThickness();
			isInit = true;
		}
		else if (thickness != style.GetThickness())
		{
			thickness = std::nullopt;
		}
	};

	m_enumerator(callback);

	return thickness;
}

void CGroupOutlineStyle::SetThickness(double thickness)
{
	OutlineStyleCallback callback = [&](IOutlineStyle& style) {
		style.SetThickness(thickness);
	};

	m_enumerator(callback);
}