#pragma once
#include "Menu.h"
#include "MultiGumballMachine.h"
#include <functional>
#include <iostream>

using namespace std::placeholders;
using namespace with_state;

class CGumballMachineControl
{
public:
	CGumballMachineControl()
		: m_menu(std::cin, std::cout)
		, m_machine(0)
	{
		m_menu.AddItem("help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](std::istream&) { m_menu.Exit(); });
		m_menu.AddItem("insertQuarter", "inserting quarter", std::bind(&CGumballMachineControl::InsertQuarter, this, _1));
		m_menu.AddItem("ejectQuarter", "eject quarters", std::bind(&CGumballMachineControl::EjectQuarter, this, _1));
		m_menu.AddItem("turnCrank", "turn crunk", std::bind(&CGumballMachineControl::TurnCrank, this, _1));
		m_menu.AddItem("toString", "print machine info", std::bind(&CGumballMachineControl::ToString, this, _1));
		m_menu.AddItem("refill", "refill machine", std::bind(&CGumballMachineControl::Refill, this, _1));
	}

	void Run()
	{
		m_menu.Run();
	}

private:
	void InsertQuarter(std::istream&)
	{
		m_machine.InsertQuarter();
	}
	void EjectQuarter(std::istream&)
	{
		m_machine.EjectQuarter();
	}
	void TurnCrank(std::istream&)
	{
		m_machine.TurnCrank();
	}
	void ToString(std::istream&)
	{
		std::cout << m_machine.ToString();
	}
	void Refill(std::istream& in)
	{
		unsigned gumballCount;
		in >> gumballCount;
		m_machine.Refill(gumballCount);
	}
	CMenu m_menu;
	CGumballMachine m_machine;
};
