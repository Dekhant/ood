#pragma once
#include <sstream>

namespace
{
	std::string CreateGumballMachineState(unsigned gumballCount, unsigned quarterCount, std::string const& state)
	{
		std::stringstream ss;
		ss << "Mighty Gumball, Inc. "
			<< "C++-enabled Standing Gumball Model #2016 (with state)\n"
			<< "Inventory: "
			<< gumballCount
			<< " gumball"
			<< (gumballCount != 1 ? "s\n" : "\n")
			<< "Quarters count: "
			<< quarterCount
			<< " quarter"
			<< (quarterCount != 1 ? "s\n" : "\n")
			<< "Machine is "
			<< state
			<< "\n";
		return ss.str();
	}
} // namespace