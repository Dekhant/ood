#pragma once
#include "ConstDocumentItem.h"
#include "DocumentItem.h"
#include <boost/optional.hpp>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
class IParagraph;
class IImage;

typedef std::filesystem::path Path;
using boost::optional;
using boost::none;

class IDocument
{
public:
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		optional<size_t> position = none)
		= 0;

	virtual std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none)
		= 0;

	virtual size_t GetItemsCount() const = 0;

	virtual CConstDocumentItem GetItem(size_t index) const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	virtual void DeleteItem(size_t index) = 0;

	virtual std::string GetTitle() const = 0;

	virtual void SetTitle(const std::string& title) = 0;

	virtual bool CanUndo() const = 0;

	virtual void Undo() = 0;

	virtual bool CanRedo() const = 0;

	virtual void Redo() = 0;

	virtual void Save(const Path& path) const = 0;

	virtual ~IDocument() = default;
};