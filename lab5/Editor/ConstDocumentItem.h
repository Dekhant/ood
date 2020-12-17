#pragma once
#include "IImage.h"
#include "IParagraph.h"
#include <memory>
#include <variant>

class CConstDocumentItem
{
public:
	typedef std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>> Item;

	CConstDocumentItem(Item const& item);

	std::shared_ptr<const IImage> GetImage() const;
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	Item m_item;
};