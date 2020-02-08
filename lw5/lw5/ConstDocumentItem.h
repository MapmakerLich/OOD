#pragma once

#include "IParagraph.h"
#include "IImage.h"

using namespace std;

class CConstDocumentItem
{
public:
	CConstDocumentItem(shared_ptr<IParagraph> paragraph)
		: m_paragraph(paragraph)
	{
	}
	CConstDocumentItem(shared_ptr<IImage> image)
		: m_image(image)
	{
	}
	virtual ~CConstDocumentItem() = default;

	shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}
	shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}

protected:
	shared_ptr<IParagraph> m_paragraph;
	shared_ptr<IImage> m_image;
};
