#pragma once

#include "PictureDraft.h"
#include "ShapeFactory.h"
#include "Designer.h"
#include "Canvas.h"
#include "Painter.h"
#include <iostream>

using namespace std;

class CClient
{
public:
	void CreatePictureDraft(istream& strm)
	{
		CShapeFactory shapeFactory;
		CDesigner designer(shapeFactory);
		m_pictureDraft = make_unique<CPictureDraft>(designer.CreateDraft(strm));
	}
	void DrawPicture(ICanvas& canvas) const
	{
		if (m_pictureDraft == nullptr)
		{
			throw runtime_error("There is no picture draft");
		}

		CPainter painter;
		painter.DrawPicture(*m_pictureDraft, canvas);
	}

private:
	std::unique_ptr<CPictureDraft> m_pictureDraft;
};