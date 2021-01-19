#include "../Editor/Menu.h"
#include "../../catch/catch.hpp"
#include <sstream>

TEST_CASE("AddItem must add command to menu")
{
	std::istringstream iss("testCommand");
	std::ostringstream oss;
	CMenu menu(iss, oss);

	std::stringstream testss;
	menu.AddItem("testCommand", "description", [&](std::istream& in) { testss << "do command"; });
	menu.Run();
	CHECK(testss.str() == "do command");
}

TEST_CASE("ShowInstructions prints all menu commands")
{
	std::istringstream iss;
	std::ostringstream oss;
	CMenu menu(iss, oss);

	menu.AddItem("command1", "description1", [](std::istream& in) {});
	menu.AddItem("command2", "description2", [](std::istream& in) {});

	menu.ShowInstructions();

	std::string instruction = "Commands list:\n  command1: description1\n  command2: description2\n";
	CHECK(oss.str() == instruction);
}

TEST_CASE("Menu prints message on invalid command")
{
	std::istringstream iss("command2");
	std::ostringstream oss;
	CMenu menu(iss, oss);

	menu.AddItem("command1", "description1", [](std::istream& in) {});
	CHECK_NOTHROW(menu.Run());

	std::string result = "Commands list:\n  command1: description1\n>Unknown command\n>";
	CHECK(oss.str() == result);
}

TEST_CASE("Exit() stops execution of commands")
{
	std::istringstream iss("command1\ncommand2\nexit\ncommand1");
	std::ostringstream oss;
	CMenu menu(iss, oss);

	std::stringstream testss;
	menu.AddItem("exit", "exit", [&](std::istream&) { menu.Exit(); });
	menu.AddItem("command1", "description1", [&](std::istream& in) { testss << "c1"; });
	menu.AddItem("command2", "description2", [&](std::istream& in) { testss << "c2"; });

	menu.Run();

	std::string result = "c1c2";
	CHECK(testss.str() == result);
}