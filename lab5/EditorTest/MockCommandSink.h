#pragma once
#include "../Editor/ICommandSink.h"

class CMockCommandSink : public ICommandSink
{

public:
	void SaveCommand(ICommandPtr&& command) override
	{
		++m_countCommands;
	}

	int GetCountCommand() const
	{
		return m_countCommands;
	}

private:
	int m_countCommands = 0;
};