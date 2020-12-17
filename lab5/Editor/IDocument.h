#pragma once
#include "ConstDocumentItem.h"
#include "DocumentItem.h"
#include "IImage.h"
#include "IParagraph.h"
#include <memory>
#include <optional>
#include <string>

class IDocument
{
public:
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt)
		= 0;

	virtual std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		std::optional<size_t> position = std::nullopt)
		= 0;

	virtual size_t GetItemsCount() const = 0;

	virtual CConstDocumentItem GetItem(size_t index) const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;
	virtual void DeleteItem(size_t index) = 0;

	virtual void ReplaceParagraphText(size_t index, const std::string& text) = 0;
	virtual void ResizeImage(size_t index, int width, int height) = 0;

	virtual std::string GetTitle() const = 0;
	virtual void SetTitle(const std::string& title) = 0;

	virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;

	virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;

	virtual void Save(const Path& path) const = 0;

	virtual ~IDocument() = default;
};