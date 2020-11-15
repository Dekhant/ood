#include "Slide.h"
#include <stdexcept>

CSlide::CSlide(double width, double height)
	: m_width(width)
	, m_height(height)
{
}

void CSlide::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

void CSlide::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
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

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index) const
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_shapes.at(index);
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("Index is out of range");
	}
	m_shapes.erase(m_shapes.begin() + index);
}