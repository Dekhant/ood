#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle();

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	bool m_isEnabled = true;
	RGBAColor m_color;
};