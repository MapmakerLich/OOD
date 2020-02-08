#pragma once

#include "AbstractCommand.h"
#include <string>

using namespace std;

class CChangeStringCommand : public CAbstractCommand
{
public:
	CChangeStringCommand(string& target, const string& newValue)
		: m_target(target)
		, m_newValue(newValue)
	{
	}

protected:
	void DoExecute()
	{
		m_newValue.swap(m_target);
	}
	void DoUnexecute()
	{
		m_newValue.swap(m_target);
	}
private:
	std::string& m_target;
	std::string m_newValue;
};
