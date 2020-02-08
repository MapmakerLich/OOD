#pragma once

#include "AbstractCommand.h"
#include "IImage.h"

using namespace std;	

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(shared_ptr<IImage> target, int width, int height)
		: m_target(target)
		, m_newWidth(width)
		, m_newHeight(height)
	{
	}

protected:
	void DoExecute() override
	{
		int tmpWidth = m_target->GetWidth();
		int tmpHeight = m_target->GetHeight();
		swap(m_newWidth, tmpWidth);
		swap(m_newHeight, tmpHeight);
		m_target->Resize(tmpWidth, tmpHeight);
	}
	void DoUnexecute()
	{
		int tmpWidth = m_target->GetWidth();
		int tmpHeight = m_target->GetHeight();
		swap(m_newWidth, tmpWidth);
		swap(m_newHeight, tmpHeight);
		m_target->Resize(tmpWidth, tmpHeight);
	}

private:
	shared_ptr<IImage> m_target;
	int m_newWidth;
	int m_newHeight;
};
