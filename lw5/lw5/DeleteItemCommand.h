#pragma once

#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <vector>

using namespace std;

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(vector<CDocumentItem>& target, size_t index)
		: m_target(target)
		, m_index(index)
		, m_item(GetDocumentItem())
	{
	}

protected:
	void DoExecute() override
	{
		m_target.erase(m_target.begin() + m_index);
	}
	void DoUnexecute() override
	{
		m_target.insert(m_target.begin() + m_index, m_item);
	}

private:
	vector<CDocumentItem>& m_target;
	size_t m_index;
	CDocumentItem m_item;

	CDocumentItem GetDocumentItem()
	{
		if (m_index >= m_target.size())
		{
			throw runtime_error("The item number exceeds the number of items in the document");
		}
		return m_target[m_index];
	}
};
