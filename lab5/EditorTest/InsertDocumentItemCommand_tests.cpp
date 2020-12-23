#include "../Editor/Image.h"
#include "../Editor/InsertDocumentItemCommand.h"
#include "../Editor/Paragraph.h"
#include "MockCommandSink.h"
#include "../catch/catch.hpp"

namespace
{
	CMockCommandSink commandSink;
	CDocumentItem paragraph1(std::make_shared<CParagraph>("text1", commandSink));
	CDocumentItem paragraph2(std::make_shared<CParagraph>("text2", commandSink));
} // namespace

TEST_CASE("It is impossible to insert a document in a nonexistent position")
{
	std::vector<CDocumentItem> items = { paragraph1 };

	CHECK_THROWS(CInsertDocumentItemCommand(paragraph2, items, 1));

	SECTION("If position isn't passed, then the element will be added to the end")
	{
		CHECK_NOTHROW(CInsertDocumentItemCommand(paragraph2, items));
	}
}

TEST_CASE("Executing the command adds an item to the specified position")
{
	std::vector<CDocumentItem> items{};

	CInsertDocumentItemCommand command1(paragraph2, items);
	CHECK_NOTHROW(command1.Execute());
	CHECK(items.back().GetParagraph() == paragraph2.GetParagraph());

	CInsertDocumentItemCommand command2(paragraph1, items, 0);
	CHECK_NOTHROW(command2.Execute());
	CHECK(items.front().GetParagraph() == paragraph1.GetParagraph());
}

TEST_CASE("Unxecuting the command removes an item from the specified position")
{
	std::vector<CDocumentItem> items{};

	CInsertDocumentItemCommand command1(paragraph2, items);
	command1.Execute();

	CInsertDocumentItemCommand command2(paragraph1, items, 0);
	command2.Execute();
	CHECK_NOTHROW(command2.Unexecute());
	CHECK(items.front().GetParagraph() != paragraph1.GetParagraph());

	CHECK_NOTHROW(command1.Unexecute());
	CHECK(items.size() == 0);
}

TEST_CASE("If command to insert image is canceled and command is destroyed, then image file must be deleted")
{
	CDocumentItem image(std::make_shared<CImage>("image.jpg", 200, 300, commandSink));
	std::vector<CDocumentItem> items{};

	Path path = image.GetImage()->GetPath();

	CInsertDocumentItemCommand command(image, items);
	command.Execute();
	CHECK(items.front().GetImage() == image.GetImage());

	command.Unexecute();
	CHECK(std::filesystem::exists(path));

	command.~CInsertDocumentItemCommand();
	CHECK_FALSE(std::filesystem::exists(path));
}