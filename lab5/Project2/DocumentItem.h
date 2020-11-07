#pragma once
#include "ConstDocumentItem.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(const IParagraphPtr& paragraph);
	CDocumentItem(const IImagePtr& image);

	std::shared_ptr<IImage> GetImage();

	std::shared_ptr<IParagraph> GetParagraph();
};

typedef std::shared_ptr<CDocumentItem> DocumentItemPtr;