#pragma once
#include "IOutlineStyle.h"

typedef std::function<void(OutlineStyleCallback)> OutlineStyleEnumerator;

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(OutlineStyleEnumerator enumerator);

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	std::optional<double> GetThickness() const override;
	void SetThickness(double thickness) override;

private:
	OutlineStyleEnumerator m_enumerator;
};