#pragma once
#include "../Editor/AbstractCommand.h"

class CMockCommand : public CAbstractCommand
{
public:
	void DoExecute() override
	{
	}

	void DoUnexecute() override
	{
	}
};