#pragma once

#include "AbstractCommand.h"
#include "IParagraph.h"

using namespace std;

class CReplaceTextCommand : public CAbstractCommand
{
public:
	CReplaceTextCommand(shared_ptr<IParagraph> target, const string& newText)
		: m_target(target)
		, m_newText(newText)
	{
	}

protected:
	void DoExecute() override
	{
		string tmpStr = m_target->GetText();
		m_newText.swap(tmpStr);
		m_target->SetText(tmpStr);
	}
	void DoUnexecute() override
	{
		string tmpStr = m_target->GetText();
		m_newText.swap(tmpStr);
		m_target->SetText(tmpStr);
	}

private:
	shared_ptr<IParagraph> m_target;
	string m_newText;
};
