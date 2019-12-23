#pragma once
#include "PictureDraft.h"
#include "IShapeFactory.h"
#include <iostream>

using namespace std;

class CDesigner
{
public:
	CDesigner(IShapeFactory& factory)
		:m_factory(factory)
	{
	}

	CPictureDraft CreateDraft(istream& inputData)
	{
		CPictureDraft draft;
		string line;
		while (getline(inputData, line))
		{
			try
			{
				draft.AddShape(m_factory.CreateShape(line));
			}
			catch (const invalid_argument& exc)
			{
				cout << exc.what() << endl;
			}
		}
		return draft;
	}

private:
	IShapeFactory& m_factory;
};
