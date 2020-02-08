#pragma once

#include "ICanvas.h"

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw(ICanvas& canvas) const = 0;
};
