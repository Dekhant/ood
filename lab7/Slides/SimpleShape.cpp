#include "SimpleShape.h"
#include <memory>
#include "OutlineStyle.h"
#include "FillStyle.h"

CSimpleShape::CSimpleShape()
	: m_outlineStyle(std::make_shared<COutlineStyle>())
	, m_fillStyle(std::make_shared<CFillStyle>())
{
}

void CSimpleShape::Draw(ICanvas& canvas)
{
	if (*m_fillStyle->IsEnabled())
	{
		canvas.SetFillColor(*m_fillStyle->GetColor());
	}

	if (*m_outlineStyle->IsEnabled())
	{
		canvas.SetLineColor(*m_outlineStyle->GetColor());
		canvas.SetLineThickness(*m_outlineStyle->GetThickness());
	}
	DrawingBehavior(canvas);
}

std::shared_ptr<IStyle> CSimpleShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> CSimpleShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IOutlineStyle> CSimpleShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const IOutlineStyle> CSimpleShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IShapeGroup> CSimpleShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IShapeGroup> CSimpleShape::GetGroup() const
{
	return nullptr;
}