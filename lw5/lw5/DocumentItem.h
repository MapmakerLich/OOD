#pragma once

#include "ConstDocumentItem.h"

using namespace std;

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(paragraph)
	{
	}
	CDocumentItem(shared_ptr<IImage> image)
		: CConstDocumentItem(image)
	{
	}

	shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}
	shared_ptr<IImage> GetImage()
	{
		return m_image;
	}
};
