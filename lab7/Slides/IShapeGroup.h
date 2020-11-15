#pragma once
#include "IShape.h"
#include <memory>

class IShapeGroup : public IShape
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual void InsertShape(std::shared_ptr<IShape> shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapeGroup() = default;
};
