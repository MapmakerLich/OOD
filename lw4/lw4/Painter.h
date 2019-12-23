#pragma once
#include "PictureDraft.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas) const
	{
		for (size_t i = 0; i < draft.GetShapesCount(); i++)
		{
			draft[i].Draw(canvas);
		}
	}
};
