#include "../Editor/Editor.h"
#include "../catch/catch.hpp"
#include <sstream>

TEST_CASE("Run() starts processing the input stream")
{
	std::stringstream iss("insertParagraph end hello world");
	std::stringstream oss;
	CEditor editor(iss, oss);

	CHECK_NOTHROW(editor.Run());
}

namespace
{
	std::string GetInstruction()
	{
		std::stringstream ss;
		ss << "Commands list:\n"
			<< "  help: Help\n"
			<< "  exit: Exit\n"
			<< "  insertParagraph: Inserting paragraph. Args: <position>|end <text>\n"
			<< "  insertImage: Inserting image. Args: <position>|end <width> <height> <path>\n"
			<< "  setTitle: Changes title. Args: <new title>\n"
			<< "  list: Show document\n"
			<< "  replaceText: Replace paragraph text. Args: <position> <text>\n"
			<< "  resizeImage: Resize image. Args: <position> <width> <height>\n"
			<< "  deleteItem: Delete item. Args: <position>\n"
			<< "  undo: Undo command\n"
			<< "  redo: Redo undone command\n"
			<< "  save: Save to HTML file. Args: <path>\n"
			<< ">";
		return ss.str();
	}

	void CheckCommandForExpectedResult(std::string const& command, std::string const& result)
	{
		std::stringstream iss(command);
		std::stringstream oss;
		CEditor editor(iss, oss);
		CHECK_NOTHROW(editor.Run());
		CHECK(oss.str() == (GetInstruction() + result + ">"));
	}
} // namespace

TEST_CASE("InsertParagraph() takes position and text from stream")
{
	CheckCommandForExpectedResult("insertParagraph end hello world", "");

	SECTION("invalid position")
	{
		CheckCommandForExpectedResult("insertParagraph end0 hello world", "invalid stoi argument\n");
	}
	SECTION("invalid text")
	{
		CheckCommandForExpectedResult("insertParagraph end", "invalid arguments\n");
		CheckCommandForExpectedResult("insertParagraph", "invalid arguments\n");
	}
}

TEST_CASE("InsertImage() takes position, size and path from stream")
{
	CheckCommandForExpectedResult("insertImage end 200 300 image.jpg", "");
	CheckCommandForExpectedResult("insertImage 0 200 300 image.jpg", "Index cannot be greater than number of elements\n");

	SECTION("invalid position")
	{
		CheckCommandForExpectedResult("insertImage A0 200 300 image.jpg", "invalid stoi argument\n");
	}
	SECTION("invalid arguments")
	{
		CheckCommandForExpectedResult("insertImage end 200 image.jpg", "invalid arguments\n");
		CheckCommandForExpectedResult("insertImage end 200 300", "invalid arguments\n");
	}
}

TEST_CASE("SetTitle() takes title from stream")
{
	CheckCommandForExpectedResult("setTitle hello world", "");
	CheckCommandForExpectedResult("setTitle", "");
}

TEST_CASE("ReplaceText() takes position and text from stream")
{
	CheckCommandForExpectedResult("replaceText 0 hello world", "Paragraph index is out of range\n");

	SECTION("invalid arguments")
	{
		CheckCommandForExpectedResult("replaceText 0", "invalid arguments\n");
	}
}

TEST_CASE("ResizeImage() takes position and size from stream")
{
	CheckCommandForExpectedResult("resizeImage 0 200 300", "Image index is out of range\n");

	SECTION("invalid position")
	{
		CheckCommandForExpectedResult("insertImage a 200 300", "invalid arguments\n");
	}
	SECTION("invalid size")
	{
		CheckCommandForExpectedResult("insertImage 0 a a", "invalid arguments\n");
	}
}

TEST_CASE("DeleteItem() takes position from stream")
{
	CheckCommandForExpectedResult("deleteItem 0", "Index cannot be greater than number of elements\n");

	SECTION("invalid position")
	{
		CheckCommandForExpectedResult("insertImage a", "invalid arguments\n");
	}
}

TEST_CASE("Save() takes path from stream")
{
	CheckCommandForExpectedResult("save path", "");
	CheckCommandForExpectedResult("save", "");
}

TEST_CASE("Undo() checks can be done undo command and executes")
{
	CheckCommandForExpectedResult("undo", "Can't undo\n");
	CheckCommandForExpectedResult("setTitle 123\nundo", ">");
}

TEST_CASE("Redo() checks can be done redo command and executes")
{
	CheckCommandForExpectedResult("redo", "Can't redo\n");
	CheckCommandForExpectedResult("setTitle 123\nundo\nredo", ">>");
}

TEST_CASE("List() print all elements of document")
{
	std::stringstream result;
	result << ">>>  Title: 123\n"
		<< " \t0. Paragraph: hello!!\n"
		<< " \t1. Paragraph: hello world\n";
	CheckCommandForExpectedResult("setTitle 123\ninsertParagraph end hello world\ninsertParagraph 0 hello!!\nlist", result.str());
}