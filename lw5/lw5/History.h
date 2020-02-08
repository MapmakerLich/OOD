#pragma once

#include "ICommand.h"
#include <deque>

class CHistory
{
public:
	void AddAndExecuteCommand(ICommandPtr&& command)
	{
		if (m_nextCommandIndex < m_commands.size())
		{
			command->Execute();
			m_nextCommandIndex++;
			m_commands.resize(m_nextCommandIndex);
			m_commands.back() = move(command);
		}
		else
		{
			command->Execute();
			m_commands.emplace_back(move(command));
			if (m_nextCommandIndex < 10)
			{
				m_nextCommandIndex++;
			}
			else
			{
				m_commands.pop_front();
			}
		}
	}

	bool CanUndo() const
	{
		return m_nextCommandIndex != 0;
	}
	void Undo()
	{
		if (CanUndo())
		{
			m_commands[m_nextCommandIndex - 1]->Unexecute();
			m_nextCommandIndex--;
		}
	}
	bool CanRedo() const
	{
		return m_nextCommandIndex != m_commands.size();
	}
	void Redo()
	{
		if (CanRedo())
		{
			m_commands[m_nextCommandIndex]->Execute();
			m_nextCommandIndex++;
		}
	}

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};
