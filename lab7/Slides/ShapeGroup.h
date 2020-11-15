#pragma once
#include "IShapeGroup.h"
#include <vector>

class CShapeGroup : public IShapeGroup
	, public std::enable_shared_from_this<CShapeGroup>
{
public:
	CShapeGroup();

	void Draw(ICanvas& canvas) override;

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IShapeGroup> GetGroup() override;
	std::shared_ptr<const IShapeGroup> GetGroup() const override;

	size_t GetShapesCount() const override;
	void InsertShape(std::shared_ptr<IShape> shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};