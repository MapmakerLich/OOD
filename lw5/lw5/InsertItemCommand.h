#pragma once

#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "Paragraph.h"
#include <vector>
#include <optional>

using namespace std;

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(vector<CDocumentItem>& target, const CDocumentItem& item, optional<size_t> position)
		: m_target(target)
		, m_item(item)
		, m_position(position)
	{
		if (m_position != nullopt && m_position.value() > m_target.size())
		{
			throw runtime_error("The item number exceeds the number of items in the document");
		}
	}

protected:
	void DoExecute() override
	{
		if (m_position == nullopt)
		{
			m_target.push_back(m_item);
		}
		else
		{
			m_target.insert(m_target.begin() + m_position.value(), m_item);
		}
	}
	void DoUnexecute() override
	{
		if (m_position == nullopt)
		{
			m_target.pop_back();
		}
		else
		{
			m_target.erase(m_target.begin() + m_position.value());
		}
	}

private:
	vector<CDocumentItem>& m_target;
	CDocumentItem m_item;
	optional<size_t> m_position;
};