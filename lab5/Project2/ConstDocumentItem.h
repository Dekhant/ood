#pragma once
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const IParagraphPtr& paragraph);
	CConstDocumentItem(const IImagePtr& image);
	std::shared_ptr<const IImage> GetImage() const;
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	IImagePtr m_image;
	IParagraphPtr m_paragraph;
};