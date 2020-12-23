#pragma once
#include "../Editor/ReplaceParagraphTextCommand.h"
#include "../catch/catch.hpp"

TEST_CASE("ReplaceParagraphTextCommand swaps replacement and reference of replaceable strings")
{
	std::string replaceable = "123 hello";
	std::string replacement = "hello world!";

	CReplaceParagraphTextCommand command(replaceable, replacement);

	command.Execute();
	CHECK(replaceable == "hello world!");

	command.Unexecute();
	CHECK(replaceable == "123 hello");
}