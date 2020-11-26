#include "../MultiGumballMachine/NaiveMultiGumballMachine.h"
#include "CreateGumballMachineState.h"
#include "../catch/catch.hpp"

TEST_CASE("Test sold out state in NaiveGumballMachine")
{
	naive::CGumballMachine machine(0);
	CHECK(machine.ToString() == CreateGumballMachineState(0, 0, "sold out"));

	SECTION("InsertQuarter() doesn't change machine state and increase quarterCount")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(0, 1, "sold out"));
	}

	SECTION("EjectQuarter() doesn't change machine state and eject all quarters")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(0, 2, "sold out"));
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(0, 0, "sold out"));
	}

	SECTION("TurnCrank() doesn't change machine state")
	{
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(0, 0, "sold out"));
	}
}

TEST_CASE("Test has quarter state in NaiveGumballMachine")
{
	naive::CGumballMachine machine(2);
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(2, 1, "waiting for turn of crank"));

	SECTION("InsertQuarter() doesn't change machine state and increase quarterCount")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 2, "waiting for turn of crank"));
	}

	SECTION("EjectQuarter() changes machine state to NoQuarterState and eject all quarters")
	{
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 0, "waiting for quarter"));
	}

	SECTION("TurnCrank() will change machine state to SetSoldOutState if gumbollCount is 0")
	{
		naive::CGumballMachine machine(1);
		machine.InsertQuarter();
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(0, 0, "sold out"));
	}

	SECTION("TurnCrank() will change machine state to NoQuarterState if gumballCount isn't 0 and quarterCount is 0")
	{
		naive::CGumballMachine machine(2);
		machine.InsertQuarter();
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(1, 0, "waiting for quarter"));
	}

	SECTION("TurnCrank() will change machine state to HasQuarterState if gumballCount isn't 0 and quarterCount isn't 0")
	{
		naive::CGumballMachine machine(2);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(1, 1, "waiting for turn of crank"));
	}
}

TEST_CASE("Test max quarters state in NaiveGumballMachine")
{
	naive::CGumballMachine machine(2);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();

	CHECK(machine.ToString() == CreateGumballMachineState(2, 5, "quarters store is full. waiting for turn of crank"));

	SECTION("InsertQuarter() doesn't change machine state")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 5, "quarters store is full. waiting for turn of crank"));
	}

	SECTION("EjectQuarter() changes machine state to NoQuarterState and eject all quarters")
	{
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 0, "waiting for quarter"));
	}

	SECTION("TurnCrank() will change machine state to SoldOutState if gumbullCount is 0")
	{
		naive::CGumballMachine machine(1);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(0, 4, "sold out"));
	}

	SECTION("TurnCrank() will change machine state to HasQuarterState if gumballCount isn't 0")
	{
		naive::CGumballMachine machine(2);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();

		CHECK(machine.ToString() == CreateGumballMachineState(1, 4, "waiting for turn of crank"));
	}
}

TEST_CASE("Test no quarter state in NaiveGumballMachine")
{
	naive::CGumballMachine machine(2);
	CHECK(machine.ToString() == CreateGumballMachineState(2, 0, "waiting for quarter"));

	SECTION("EjectQuarter() doesn't change machine state")
	{
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 0, "waiting for quarter"));
	}

	SECTION("TurnCrunk() doesn't change machine state")
	{
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 0, "waiting for quarter"));
	}

	SECTION("InsertQuarter() will change machine state to HasQuarterState")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, 1, "waiting for turn of crank"));
	}
}

TEST_CASE("Gumball machine store max 5 quarters in NaiveGumballMachine")
{
	naive::CGumballMachine machine(5);
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(5, 1, "waiting for turn of crank"));
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(5, 2, "waiting for turn of crank"));
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(5, 3, "waiting for turn of crank"));
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(5, 4, "waiting for turn of crank"));
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(5, 5, "quarters store is full. waiting for turn of crank"));
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(5, 5, "quarters store is full. waiting for turn of crank"));

	machine.TurnCrank();
	CHECK(machine.ToString() == CreateGumballMachineState(4, 4, "waiting for turn of crank"));
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(4, 5, "quarters store is full. waiting for turn of crank"));
}