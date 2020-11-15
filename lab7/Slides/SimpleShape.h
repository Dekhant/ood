#pragma once
#include "IShape.h"

class CSimpleShape : public IShape
{
public:
	CSimpleShape();

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IShapeGroup> GetGroup() override;
	std::shared_ptr<const IShapeGroup> GetGroup() const override;

	void Draw(ICanvas& canvas) override;
	virtual void DrawingBehavior(ICanvas& canvas) const = 0;

private:
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};