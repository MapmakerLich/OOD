#pragma once

#include "Shape.h"
#include <memory>
#include <string>

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual std::unique_ptr<CShape> CreateShape(const std::string& description) const = 0;
};
