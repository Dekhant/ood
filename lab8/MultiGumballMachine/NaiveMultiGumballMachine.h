#include <iostream>
#include <sstream>

namespace naive
{
	constexpr unsigned MAX_QUARTERS = 5;

	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,
			NoQuarter,
			HasQuarter,
			MaxQuarters,
			Sold,
		};

		CGumballMachine(unsigned count)
			: m_count(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You inserted another quarter\n";
				m_quarterCount++;
				break;
			case State::NoQuarter:
				cout << "You inserted a quarter\n";
				m_state = State::HasQuarter;
				m_quarterCount++;
				break;
			case State::HasQuarter:
				cout << "You inserted another quarter\n";
				m_quarterCount++;
				m_state = (m_quarterCount == MAX_QUARTERS) ? State::MaxQuarters : m_state;
				break;
			case State::MaxQuarters:
				std::cout << "You can't insert another quarter: max " << MAX_QUARTERS << " quarters\n";
				break;
			case State::Sold:
				cout << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::MaxQuarters:
			case State::HasQuarter:
				cout << "Quarter returned (" + std::to_string(m_quarterCount) + ")\n";
				m_quarterCount = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				cout << "You haven't inserted a quarter\n";
				break;
			case State::Sold:
				cout << "Wait for the gumball to be despensed\n";
				break;
			case State::SoldOut:
				cout << "Quarter returned (" + std::to_string(m_quarterCount) + ")\n";
				m_quarterCount = 0;
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				cout << "You turned but there's no quarter\n";
				break;
			case State::MaxQuarters:
			case State::HasQuarter:
				cout << "You turned...\n";
				m_state = State::Sold;
				if (m_quarterCount > 0)
				{
					--m_quarterCount;
				}
				Dispense();
				break;
			case State::Sold:
				cout << "Turning twice doesn't get you another gumball\n";
				break;
			}
		}

		std::string ToString() const
		{
			std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoQuarter) ? "waiting for quarter"
				: (m_state == State::HasQuarter) ? "waiting for turn of crank"
				: (m_state == State::MaxQuarters) ? "quarters store is full. waiting for turn of crank"
				: "delivering a gumball";
			std::stringstream ss;
			ss << "Mighty Gumball, Inc. "
				<< "C++-enabled Standing Gumball Model #2016 (with state)\n"
				<< "Inventory: "
				<< m_count
				<< " gumball"
				<< (m_count != 1 ? "s\n" : "\n")
				<< "Quarters count: "
				<< m_quarterCount
				<< " quarter"
				<< (m_quarterCount != 1 ? "s\n" : "\n")
				<< "Machine is "
				<< state
				<< "\n";
			return ss.str();
		}

	private:
		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				cout << "A gumball comes rolling out the slot\n";
				--m_count;
				if (m_count == 0)
				{
					cout << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				else
				{
					if (m_quarterCount > 0)
					{
						m_state = State::HasQuarter;
					}
					else
					{
						m_state = State::NoQuarter;
					}
				}
				break;
			case State::NoQuarter:
				cout << "You need to pay first\n";
				break;
			case State::MaxQuarters:
			case State::SoldOut:
			case State::HasQuarter:
				cout << "No gumball dispensed\n";
				break;
			}
		}

		unsigned m_count;
		unsigned m_quarterCount = 0;
		State m_state = State::SoldOut;
	};
} // namespace naive#pragma once
