#include "../../catch/catch.hpp"
#include "../Editor/DeleteItemCommand.h"
#include "../Editor/Image.h"
#include "../Editor/Paragraph.h"
#include "MockCommandSink.h"



namespace
{
	CMockCommandSink commandSink;
	CDocumentItem paragraph1(std::make_shared<CParagraph>("text1", commandSink));
	CDocumentItem paragraph2(std::make_shared<CParagraph>("text2", commandSink));
} // namespace

TEST_CASE("It is impossible to delete a document from a nonexistent position")
{
	std::vector<CDocumentItem> items = { paragraph1, paragraph2 };

	CHECK_THROWS(CDeleteItemCommand(items, 2));
	CHECK_NOTHROW(CDeleteItemCommand(items, 1));
}

TEST_CASE("Executing the command removes an item from the specified position")
{
	std::vector<CDocumentItem> items = { paragraph1, paragraph2 };

	CDeleteItemCommand command1(items, 1);
	CHECK_NOTHROW(command1.Execute());
	CHECK(items.back().GetParagraph() == paragraph1.GetParagraph());

	CDeleteItemCommand command2(items, 0);
	CHECK_NOTHROW(command2.Execute());
	CHECK(items.size() == 0);
}

TEST_CASE("Unxecuting the command adds an item to the specified position")
{
	std::vector<CDocumentItem> items = { paragraph1, paragraph2 };

	CDeleteItemCommand command1(items, 1);
	command1.Execute();

	CDeleteItemCommand command2(items, 0);
	command2.Execute();
	CHECK_NOTHROW(command2.Unexecute());
	CHECK(items.back().GetParagraph() == paragraph1.GetParagraph());

	CHECK_NOTHROW(command1.Unexecute());
	CHECK(items.back().GetParagraph() == paragraph2.GetParagraph());
}

TEST_CASE("If command to delete image is executed and command is destroyed, then image file must be deleted")
{
	CDocumentItem image(std::make_shared<CImage>("image.jpg", 200, 300, commandSink));
	std::vector<CDocumentItem> items = { image };

	Path path = image.GetImage()->GetPath();

	CDeleteItemCommand command(items, 0);
	command.Execute();
	CHECK(items.size() == 0);
	CHECK(std::filesystem::exists(path));

	command.~CDeleteItemCommand();
	CHECK_FALSE(std::filesystem::exists(path));
}