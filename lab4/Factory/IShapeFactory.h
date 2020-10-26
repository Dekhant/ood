#pragma once
#include <memory>
#include "Shape.h"
#include <string>

struct IShapeFactory
{
	virtual std::unique_ptr<CShape> CreateShape(const std::string & description) const = 0;

	virtual ~IShapeFactory() = default;
};