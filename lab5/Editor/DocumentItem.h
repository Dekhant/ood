#pragma once
#include "ConstDocumentItem.h"
#include <variant>

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(CConstDocumentItem::Item const& item);

	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();
};