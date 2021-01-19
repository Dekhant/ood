#include "../MultiGumballMachineV2/MultiGumballMachineV2.h"
#include "../MultiGumballMachineTests/CreateGumballMachineState.h"
#include "../../catch/catch.hpp"
using namespace with_state;

TEST_CASE("Refill in SoldOutState must change state")
{
	SECTION("There are 5 quarters")
	{
		CGumballMachine machine(0);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		CHECK_NOTHROW(machine.Refill(3));
		CHECK(machine.ToString() == CreateGumballMachineState(3, 5, "quarters store is full. waiting for turn of crank"));
	}

	SECTION("There are quarters")
	{
		CGumballMachine machine(0);
		machine.InsertQuarter();
		machine.InsertQuarter();

		CHECK_NOTHROW(machine.Refill(5));
		CHECK(machine.ToString() == CreateGumballMachineState(5, 2, "waiting for turn of crank"));
	}

	SECTION("There are no quarters")
	{
		CGumballMachine machine(0);

		CHECK_NOTHROW(machine.Refill(5));
		CHECK(machine.ToString() == CreateGumballMachineState(5, 0, "waiting for quarter"));
	}
}

TEST_CASE("Refill in HasQuarterState mustn't change state")
{
	CGumballMachine machine(3);
	machine.InsertQuarter();
	machine.InsertQuarter();

	CHECK(machine.ToString() == CreateGumballMachineState(3, 2, "waiting for turn of crank"));

	CHECK_NOTHROW(machine.Refill(5));
	CHECK(machine.ToString() == CreateGumballMachineState(5, 2, "waiting for turn of crank"));
}

TEST_CASE("Refill in MaxQuartersState mustn't change state")
{
	CGumballMachine machine(3);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();

	CHECK(machine.ToString() == CreateGumballMachineState(3, 5, "quarters store is full. waiting for turn of crank"));

	CHECK_NOTHROW(machine.Refill(6));
	CHECK(machine.ToString() == CreateGumballMachineState(6, 5, "quarters store is full. waiting for turn of crank"));
}

TEST_CASE("Refill in NoQuarterState mustn't change state")
{
	CGumballMachine machine(3);

	CHECK(machine.ToString() == CreateGumballMachineState(3, 0, "waiting for quarter"));

	CHECK_NOTHROW(machine.Refill(5));
	CHECK(machine.ToString() == CreateGumballMachineState(5, 0, "waiting for quarter"));
}