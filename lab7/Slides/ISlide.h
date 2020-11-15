#pragma once
#include "CommonTypes.h"
#include "IDrawable.h"
#include "IShapes.h"
#include <optional>

class ISlide : public IDrawable, public IShapes
{
public:
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;

	virtual ~ISlide() = default;
};