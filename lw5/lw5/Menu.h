#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class CMenu
{
public:
	using Command = function<void(istream& args)>;

	CMenu(istream& inStrm, ostream& outStrm)
		: m_inStrm(inStrm)
		, m_outStrm(outStrm)
	{
	}

	void AddItem(const string& shortcut, const string& description, const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}
	void Run()
	{
		ShowInstructions();

		string command;
		while (getline(m_inStrm, command) && ExecuteCommand(command))
		{
		}
	}
	void ShowInstructions() const
	{
		m_outStrm << "Commands list:\n";
		for (auto& item : m_items)
		{
			m_outStrm << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}
	void Exit()
	{
		m_exit = true;
	}

private:
	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};

	std::istream& m_inStrm;
	std::ostream& m_outStrm;
	std::vector<Item> m_items;
	bool m_exit = false;

	bool ExecuteCommand(const string& command)
	{
		istringstream iss(command);
		string name;
		iss >> name;

		m_exit = false;
		auto it = find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
			return item.shortcut == name;
		});

		if (it != m_items.end())
		{
			it->command(iss);
		}
		else
		{
			m_outStrm << "Unknown command\n";
		}
		return !m_exit;
	}
};
