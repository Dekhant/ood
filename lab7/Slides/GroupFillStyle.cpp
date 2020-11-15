#include "GroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(FillStyleEnumerator enumerator)
	: m_enumerator(enumerator)
{
}

std::optional<bool> CGroupFillStyle::IsEnabled() const
{
	std::optional<bool> isEnabled = std::nullopt;
	bool isInit = false;

	StyleCallback callback = [&](IStyle& style) {
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

void CGroupFillStyle::Enable(bool enable)
{
	StyleCallback callback = [&](IStyle& style) {
		style.Enable(enable);
	};

	m_enumerator(callback);
}

std::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	std::optional<RGBAColor> color = std::nullopt;
	bool isInit = false;

	StyleCallback callback = [&](IStyle& style) {
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

void CGroupFillStyle::SetColor(RGBAColor color)
{
	StyleCallback callback = [&](IStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(callback);
}