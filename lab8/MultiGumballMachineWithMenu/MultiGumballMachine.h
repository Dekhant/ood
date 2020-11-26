#include <iostream>
#include <sstream>

namespace with_state
{

	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual void Refill(unsigned count) = 0;
		virtual std::string ToString() const = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		virtual void ReleaseQuarter() = 0;
		virtual unsigned GetBallCount() const = 0;
		virtual unsigned GetQuarterCount() const = 0;
		virtual void AddQuarter() = 0;
		virtual void RefillImpl(unsigned count) = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;
		virtual void SetMaxQuartersState() = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{
		}
		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				if (m_gumballMachine.GetQuarterCount() > 0)
				{
					m_gumballMachine.SetHasQuarterState();
				}
				else
				{
					m_gumballMachine.SetNoQuarterState();
				}
			}
		}
		void Refill(unsigned count)
		{
			std::cout << "Cannot refill  while giving a gumball\n";
		}
		std::string ToString() const override
		{
			return "delivering a gumball";
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	constexpr unsigned MAX_QUARTERS = 5;

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{
		}

		void InsertQuarter() override
		{
			m_gumballMachine.AddQuarter();
		}
		void EjectQuarter() override
		{
			std::cout << "Quarter returned (" + std::to_string(m_gumballMachine.GetQuarterCount()) + ")\n";
			while (m_gumballMachine.GetQuarterCount() != 0)
			{
				m_gumballMachine.ReleaseQuarter();
			}
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned count)
		{
			m_gumballMachine.RefillImpl(count);
			if (m_gumballMachine.GetQuarterCount() == MAX_QUARTERS)
			{
				m_gumballMachine.SetMaxQuartersState();
			}
			else if (m_gumballMachine.GetQuarterCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
		std::string ToString() const override
		{
			return "sold out";
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{
		}

		void InsertQuarter() override
		{
			m_gumballMachine.AddQuarter();
			if (m_gumballMachine.GetQuarterCount() == MAX_QUARTERS)
			{
				m_gumballMachine.SetMaxQuartersState();
			}
		}
		void EjectQuarter() override
		{
			std::cout << "Quarter returned (" + std::to_string(m_gumballMachine.GetQuarterCount()) + ")\n";
			while (m_gumballMachine.GetQuarterCount() != 0)
			{
				m_gumballMachine.ReleaseQuarter();
			}
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.ReleaseQuarter();
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned count)
		{
			m_gumballMachine.RefillImpl(count);
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{
		}

		void InsertQuarter() override
		{
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}
		void Refill(unsigned count)
		{
			m_gumballMachine.RefillImpl(count);
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	class CMaxQuartersState : public IState
	{
	public:
		CMaxQuartersState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{
		}

		void InsertQuarter() override
		{
			std::cout << "You can't insert another quarter: max " << MAX_QUARTERS << " quarters\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Quarter returned (" + std::to_string(m_gumballMachine.GetQuarterCount()) + ")\n";
			while (m_gumballMachine.GetQuarterCount() != 0)
			{
				m_gumballMachine.ReleaseQuarter();
			}
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.ReleaseQuarter();
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned count) override
		{
			m_gumballMachine.RefillImpl(count);
		}
		std::string ToString() const override
		{
			return "quarters store is full. waiting for turn of crank";
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_maxQuartersState(*this)
			, m_state(&m_soldOutState)
			, m_count(numBalls)
		{
			if (m_count > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		void Refill(unsigned count)
		{
			m_state->Refill(count);
		}
		std::string ToString() const
		{
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
				<< m_state->ToString()
				<< "\n";
			return ss.str();
		}

	private:
		unsigned GetBallCount() const override
		{
			return m_count;
		}
		unsigned GetQuarterCount() const override
		{
			return m_quarterCount;
		}
		virtual void ReleaseBall() override
		{
			if (m_count != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_count;
			}
		}
		virtual void ReleaseQuarter() override
		{
			if (m_quarterCount != 0)
			{
				--m_quarterCount;
			}
		}
		void AddQuarter() override
		{
			if (GetQuarterCount() < MAX_QUARTERS)
			{
				m_quarterCount++;
				std::cout << "You inserted a quarter\n";
			}
			else
			{
				std::cout << "You can't insert another quarter: max " << MAX_QUARTERS << " quarters\n";
			}
		}
		void RefillImpl(unsigned count)
		{
			m_count = count;
			std::cout << "Refill gumballs: " << count << "\n";
		}
		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}
		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}
		void SetSoldState() override
		{
			m_state = &m_soldState;
		}
		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
		void SetMaxQuartersState() override
		{
			m_state = &m_maxQuartersState;
		}

	private:
		unsigned m_count = 0;
		unsigned m_quarterCount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		CMaxQuartersState m_maxQuartersState;
		IState* m_state;
	};

} // namespace with_state