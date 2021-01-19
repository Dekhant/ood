#define CATCH_CONFIG_MAIN
#include "../../catch/catch.hpp"
#include "../GumballMachine/GumballMachine.h"
using namespace with_state;

std::string CreateGumballMachineState(unsigned gumballCount, std::string const& state)
{
	std::stringstream ss;
	ss << "Mighty Gumball, Inc. "
		<< "C++-enabled Standing Gumball Model #2016 (with state)\n"
		<< "Inventory: "
		<< gumballCount
		<< " gumball"
		<< (gumballCount != 1 ? "s\n" : "\n")
		<< "Machine is "
		<< state
		<< "\n";
	return ss.str();
}

TEST_CASE("Test sold out state")
{
	CGumballMachine machine(0);
	CHECK(machine.ToString() == CreateGumballMachineState(0, "sold out"));

	SECTION("InsertQuarter() doesn't change machine state")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(0, "sold out"));
	}

	SECTION("EjectQuarter() doesn't change machine state")
	{
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(0, "sold out"));
	}

	SECTION("TurnCrank() doesn't change machine state")
	{
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(0, "sold out"));
	}
}

TEST_CASE("Test has quarter state")
{
	CGumballMachine machine(2);
	machine.InsertQuarter();
	CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for turn of crank"));

	SECTION("InsertQuarter() doesn't change machine state")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for turn of crank"));
	}

	SECTION("EjectQuarter() changes machine state to NoQuarterState")
	{
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for quarter"));
	}

	SECTION("TurnCrank() will change machine state to SetSoldOutState if gumbollCount is 0")
	{
		CGumballMachine machine(1);
		machine.InsertQuarter();
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(0, "sold out"));
	}

	SECTION("TurnCrank() will change machine state to NoQuarterState if gumbollCount isn't 0")
	{
		CGumballMachine machine(2);
		machine.InsertQuarter();
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(1, "waiting for quarter"));
	}
}

TEST_CASE("Test no quarter state")
{
	CGumballMachine machine(2);
	CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for quarter"));

	SECTION("EjectQuarter() doesn't change machine state")
	{
		machine.EjectQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for quarter"));
	}

	SECTION("TurnCrunk() doesn't change machine state")
	{
		machine.TurnCrank();
		CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for quarter"));
	}

	SECTION("InsertQuarter() will change machine state to HasQuarterState")
	{
		machine.InsertQuarter();
		CHECK(machine.ToString() == CreateGumballMachineState(2, "waiting for turn of crank"));
	}
}