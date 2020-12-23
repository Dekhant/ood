#pragma once
#include "../Editor/SetTitleCommand.h"
#include "../catch/catch.hpp"

TEST_CASE("SetTitleCommand swaps replacement and reference of replaceable strings")
{
	std::string replaceable = "123";
	std::string replacement = "all";

	CSetTitleCommand command(replaceable, replacement);

	command.Execute();
	CHECK(replaceable == "all");

	command.Unexecute();
	CHECK(replaceable == "123");
}