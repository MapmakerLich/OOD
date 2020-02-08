#pragma once

#include "IParagraph.h"

using namespace std;

class CParagraph : public IParagraph
{
public:
	CParagraph(const string& text)
		: m_text(text)
	{
	}

	string GetText() const override
	{
		return m_text;
	}
	void SetText(const string& text) override
	{
		m_text = text;
	}

private:
	string m_text;
};
