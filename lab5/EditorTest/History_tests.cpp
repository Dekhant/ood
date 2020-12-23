#include "../Editor/History.h"
#include "../catch/catch.hpp"
#include <memory>
#include "MockCommand.h"

TEST_CASE("CanUndo checks can be done undo")
{
	CHistory history;

	SECTION("empty history")
	{
		CHECK_FALSE(history.CanUndo());
	}

	SECTION("history contains elements")
	{
		history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
		history.AddAndExecuteCommand(std::make_unique<CMockCommand>());

		CHECK(history.CanUndo());

		history.Undo();
		CHECK(history.CanUndo());
		history.Undo();
		CHECK_FALSE(history.CanUndo());
	}
}

TEST_CASE("CanRedo checks can be done redo")
{
	CHistory history;

	SECTION("empty history")
	{
		CHECK_FALSE(history.CanRedo());
	}

	SECTION("history contains elements")
	{
		history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
		history.AddAndExecuteCommand(std::make_unique<CMockCommand>());

		CHECK_FALSE(history.CanRedo());

		history.Undo();
		CHECK(history.CanRedo());
		history.Redo();
		CHECK_FALSE(history.CanRedo());
	}
}

TEST_CASE("Undo and redo commands")
{
	CHistory history;
	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());

	history.Undo();
	CHECK(history.CanUndo());
	history.Undo();
	CHECK_FALSE(history.CanUndo());

	CHECK(history.CanRedo());
	history.Redo();
	CHECK(history.CanRedo());
	history.Redo();
	CHECK_FALSE(history.CanRedo());
}

TEST_CASE("History store 10 commands")
{
	CHistory history;
	for (int i = 0; i < 12; ++i)
	{
		history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
	}

	for (int i = 0; i < 10; ++i)
	{
		CHECK(history.CanUndo());
		history.Undo();
	}

	CHECK_FALSE(history.CanUndo());
}

TEST_CASE("if undo and change history then undo commands must be deleted")
{
	CHistory history;
	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());

	history.Undo();

	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());
	history.AddAndExecuteCommand(std::make_unique<CMockCommand>());

	int numberOfCommands = 4;
	for (int i = 0; i < numberOfCommands; ++i)
	{
		CHECK(history.CanUndo());
		history.Undo();
	}
}