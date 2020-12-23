#pragma once
#include "../Editor/ResizeImageCommand.h"
#include "../catch/catch.hpp"

TEST_CASE("ResizeImage swaps new size and references of current size")
{
	int width = 200;
	int height = 900;
	int newWidth = 300;
	int newHeight = 100;

	CResizeImageCommand command(width, height, newWidth, newHeight);

	command.Execute();
	CHECK(width == 300);
	CHECK(height == 100);

	command.Unexecute();
	CHECK(width == 200);
	CHECK(height == 900);

	SECTION("size must be in [1, 10000]")
	{
		CHECK_THROWS(CResizeImageCommand(width, height, 0, 1));
		CHECK_THROWS(CResizeImageCommand(width, height, 1000, 10001));
	}
}