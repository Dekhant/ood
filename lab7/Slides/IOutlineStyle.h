#pragma once
#include "IStyle.h"
#include <functional>

class IOutlineStyle : public IStyle
{
public:
	virtual std::optional<double> GetThickness() const = 0;
	virtual void SetThickness(double thickness) = 0;
};

typedef std::function<void(IOutlineStyle&)> OutlineStyleCallback;