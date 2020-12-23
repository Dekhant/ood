#include "../catch/catch.hpp"
#include "../Editor/Paragraph.h"
#include "../Editor/Image.h"
#include "../Editor/ConstDocumentItem.h"
#include "../Editor/DocumentItem.h"
#include "MockCommandSink.h"


TEST_CASE("Paragraph store text")
{
	CMockCommandSink commandSink;

	CParagraph paragraph("text 123", commandSink);
	CHECK(paragraph.GetText() == "text 123");

	SECTION("Set text must create new command")
	{
		paragraph.SetText("123");
		CHECK(commandSink.GetCountCommand() == 1);
	}
}

TEST_CASE("Image store path to image and size")
{
	CMockCommandSink commandSink;

	CImage image("image.jpg", 200, 300, commandSink);
	CHECK(image.GetPath() != "image.jpg");
	CHECK(image.GetWidth() == 200);
	CHECK(image.GetHeight() == 300);

	SECTION("Resize image must create new command")
	{
		CHECK_NOTHROW(image.Resize(100, 400));
		CHECK(commandSink.GetCountCommand() == 1);
	}

	SECTION("Not an image")
	{
		CHECK_THROWS(CImage("image.qwe", 200, 300, commandSink));
	}

	SECTION("Invalid size")
	{
		CHECK_THROWS(CImage("image.jpg", 0, 0, commandSink));
	}
}

TEST_CASE("CConstDocumentItem stores image or paragraph")
{
	CMockCommandSink commandSink;

	auto paragraph = std::make_shared<CParagraph>("123", commandSink);
	CConstDocumentItem paragraphDoc(paragraph);
	CHECK_FALSE(paragraphDoc.GetImage());
	CHECK(paragraphDoc.GetParagraph() == paragraph);

	auto image = std::make_shared<CImage>("image.jpg", 200, 300, commandSink);
	CConstDocumentItem imageDoc(image);
	CHECK(imageDoc.GetImage() == image);
	CHECK_FALSE(imageDoc.GetParagraph());
}

TEST_CASE("CDocumentItem stores image or paragraph")
{
	CMockCommandSink commandSink;

	auto paragraph = std::make_shared<CParagraph>("123", commandSink);
	CDocumentItem paragraphDoc(paragraph);
	CHECK_FALSE(paragraphDoc.GetImage());
	CHECK(paragraphDoc.GetParagraph() == paragraph);

	auto image = std::make_shared<CImage>("image.jpg", 200, 300, commandSink);
	CDocumentItem imageDoc(image);
	CHECK(imageDoc.GetImage() == image);
	CHECK_FALSE(imageDoc.GetParagraph());
}