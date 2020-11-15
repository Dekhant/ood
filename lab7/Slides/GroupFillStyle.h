#pragma once
#include "IStyle.h"
#include <functional>

typedef std::function<void(StyleCallback)> FillStyleEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillStyleEnumerator enumerator);

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	FillStyleEnumerator m_enumerator;
};