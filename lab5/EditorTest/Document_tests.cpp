#include "../Editor/Document.h"
#include "../catch/catch.hpp"
#include <fstream>
#include <sstream>

TEST_CASE("InsertParagraph must create paragraph from text and insert it in document")
{
	CDocument document;
	CHECK_NOTHROW(document.InsertParagraph("123"));
	CHECK_NOTHROW(document.InsertParagraph("hello world", 0));

	CHECK(document.GetItem(0).GetParagraph()->GetText() == "hello world");
	CHECK(document.GetItem(1).GetParagraph()->GetText() == "123");
}

TEST_CASE("InsertImage must create image from path and size and insert it in document")
{
	CDocument document;
	CHECK_NOTHROW(document.InsertImage("image.jpg", 200, 300));
	CHECK_NOTHROW(document.InsertImage("image.jpg", 300, 400, 0));

	CHECK(document.GetItem(0).GetImage()->GetWidth() == 300);
	CHECK(document.GetItem(0).GetImage()->GetHeight() == 400);
	CHECK(document.GetItem(1).GetImage()->GetWidth() == 200);
	CHECK(document.GetItem(1).GetImage()->GetHeight() == 300);
}

TEST_CASE("GetItemsCount must return number of elements")
{
	CDocument document;
	CHECK(document.GetItemsCount() == 0);

	document.InsertImage("image.jpg", 200, 300);
	CHECK(document.GetItemsCount() == 1);

	document.InsertParagraph("hello world", 0);
	CHECK(document.GetItemsCount() == 2);
}

TEST_CASE("DeleteItem must delete elemnt from specified position")
{
	CDocument document;
	document.InsertParagraph("hello world");

	CHECK_NOTHROW(document.DeleteItem(0));
	CHECK(document.GetItemsCount() == 0);
}

TEST_CASE("SetTitle must st title to document")
{
	CDocument document;
	document.InsertParagraph("hello world");

	CHECK_NOTHROW(document.SetTitle("title"));
	CHECK(document.GetTitle() == "title");
}

TEST_CASE("CanUndo checks can be done undo command")
{
	CDocument document;

	SECTION("empty document")
	{
		CHECK_FALSE(document.CanUndo());
	}

	SECTION("document contains elements")
	{
		document.InsertParagraph("hello world");
		document.SetTitle("title");

		CHECK(document.CanUndo());
		document.Undo();
		CHECK(document.CanUndo());
		document.Undo();
		CHECK_FALSE(document.CanUndo());
	}
}

TEST_CASE("CanRedo checks can be done redo command")
{
	CDocument document;

	SECTION("empty document")
	{
		CHECK_FALSE(document.CanRedo());
	}

	SECTION("document contains elements")
	{
		document.InsertParagraph("hello world");
		document.SetTitle("title");

		CHECK_FALSE(document.CanRedo());

		document.Undo();
		CHECK(document.CanRedo());
		document.Redo();
		CHECK_FALSE(document.CanRedo());
	}
}

TEST_CASE("ReplaceParagraphText must replace text in paragraph on specified position")
{
	CDocument document;
	document.InsertParagraph("hello world");
	document.InsertImage("image.jpg", 200, 300, 0);

	std::string text = "text";
	SECTION("index out of range")
	{
		CHECK_THROWS(document.ReplaceParagraphText(2, text));
	}

	SECTION("not a paragraph")
	{
		CHECK_THROWS(document.ReplaceParagraphText(0, text));
	}

	CHECK_NOTHROW(document.ReplaceParagraphText(1, text));
	CHECK(document.GetItem(1).GetParagraph()->GetText() == text);
}

TEST_CASE("ResizeImage must resize image on specified position")
{
	CDocument document;
	document.InsertParagraph("hello world");
	document.InsertImage("image.jpg", 200, 300);

	SECTION("index out of range")
	{
		CHECK_THROWS(document.ResizeImage(2, 600, 700));
	}
	SECTION("not an image")
	{
		CHECK_THROWS(document.ResizeImage(0, 400, 500));
	}

	CHECK_NOTHROW(document.ResizeImage(1, 900, 600));
	CHECK(document.GetItem(1).GetImage()->GetWidth() == 900);
	CHECK(document.GetItem(1).GetImage()->GetHeight() == 600);
}

std::string FileToString(const std::string& fileName)
{
	std::ifstream file(fileName);
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

TEST_CASE("Save() must create html file with document elements")
{
	CDocument document;
	document.InsertParagraph("<hello'\"&>");
	auto image = document.InsertImage("image.jpg", 200, 300);
	document.SetTitle("<'\"&title>");

	std::string directory = "out";

	if (!std::filesystem::is_directory(directory))
	{
		std::filesystem::create_directory(directory);
	}

	std::string filePath = directory + "/index.html";

	document.Save(filePath);

	std::string imagePath = image->GetPath().string();

	std::stringstream result;
	result << "<html>\n"
		<< "<head>\n"
		<< "<title>&lt;&apos;&quot;&amp;title&gt;</title>\n"
		<< "</head>\n"
		<< "<body>\n"
		<< "<p>&lt;hello&apos;&quot;&amp;&gt;</p>\n"
		<< "<img src=\"" + imagePath + "\" width=\"200\" height=\"300\" />\n"
		<< "</body>\n"
		<< "</html>\n";

	std::string file = FileToString(filePath);

	CHECK(file == result.str());
}