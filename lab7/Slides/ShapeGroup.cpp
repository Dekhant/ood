#include "ShapeGroup.h"
#include "GroupFillStyle.h"
#include "GroupOutlineStyle.h"
#include <algorithm>
#include <stdexcept>

CShapeGroup::CShapeGroup()
{
	OutlineStyleEnumerator enumerator1 = [&](OutlineStyleCallback callback) {
		for (auto& shape : m_shapes)
		{
			callback(*shape->GetOutlineStyle());
		}
	};
	m_outlineStyle = std::make_shared<CGroupOutlineStyle>(enumerator1);

	FillStyleEnumerator enumerator2 = [&](StyleCallback callback) {
		for (auto& shape : m_shapes)
		{
			callback(*shape->GetFillStyle());
		}
	};
	m_fillStyle = std::make_shared<CGroupFillStyle>(enumerator2);
}

void CShapeGroup::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

std::optional<RectD> CShapeGroup::GetFrame() const
{
	if (m_shapes.empty())
	{
		return std::nullopt;
	}

	double minX, minY, maxX, maxY;

	bool isInit = false;

	for (auto& shape : m_shapes)
	{
		if (shape->GetFrame())
		{
			auto shapeFrame = *shape->GetFrame();

			if (!isInit)
			{
				minX = shapeFrame.leftTop.x;
				minY = shapeFrame.leftTop.y;
				maxX = shapeFrame.leftTop.x + shapeFrame.width;
				maxY = shapeFrame.leftTop.y + shapeFrame.height;

				isInit = true;
			}
			else
			{
				minX = std::min(minX, shapeFrame.leftTop.x);
				minY = std::min(minY, shapeFrame.leftTop.y);

				maxX = std::max(maxX, shapeFrame.leftTop.x + shapeFrame.width);
				maxY = std::max(maxY, shapeFrame.leftTop.y + shapeFrame.height);
			}
		}
	}
	if (isInit)
	{
		return RectD{ { minX, minY }, maxX - minX, maxY - minY };
	}
	else
	{
		return std::nullopt;
	}
}

void CShapeGroup::SetFrame(const RectD& rect)
{
	auto GroupFrame = GetFrame();
	if (!GroupFrame)
	{
		return;
	}

	auto currentGroupFrame = *GroupFrame;

	for (auto& shape : m_shapes)
	{
		if (!shape->GetFrame())
		{
			continue;
		}
		auto shapeFrame = *shape->GetFrame();

		double newShapeLeft = rect.leftTop.x + (shapeFrame.leftTop.x - currentGroupFrame.leftTop.x) / currentGroupFrame.width * rect.width;
		double newShapeTop = rect.leftTop.y + (shapeFrame.leftTop.y - currentGroupFrame.leftTop.y) / currentGroupFrame.height * rect.height;
		double newShapeWidth = shapeFrame.width / currentGroupFrame.width * rect.width;
		double newShapeHeight = shapeFrame.height / currentGroupFrame.height * rect.height;

		auto newShapeFrame = RectD{ { newShapeLeft, newShapeTop }, newShapeWidth, newShapeHeight };
		shape->SetFrame(newShapeFrame);
	}
}

std::shared_ptr<IOutlineStyle> CShapeGroup::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const IOutlineStyle> CShapeGroup::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CShapeGroup::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> CShapeGroup::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IShapeGroup> CShapeGroup::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IShapeGroup> CShapeGroup::GetGroup() const
{
	return shared_from_this();
}

size_t CShapeGroup::GetShapesCount() const
{
	return m_shapes.size();
}

void CShapeGroup::InsertShape(std::shared_ptr<IShape> shape, size_t position)
{
	if (!shape)
	{
		throw std::out_of_range("Shape cannot be nullptr");
	}
	if (position == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(shape);
	}
	else if (position >= GetShapesCount())
	{
		throw std::out_of_range("Index is out of range");
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, shape);
	}
}

std::shared_ptr<IShape> CShapeGroup::GetShapeAtIndex(size_t index) const
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_shapes.at(index);
}

void CShapeGroup::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("Index is out of range");
	}
	m_shapes.erase(m_shapes.begin() + index);
}