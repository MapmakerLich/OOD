#pragma once

#include "IShape.h"
#include <vector>

using namespace std;

class CShapes
{
public:
	size_t GetShapesCount() const
	{
		return m_shapes.size();
	}

	shared_ptr<IShape> GetShapeAtIndex(size_t index)
	{
		if (index >= m_shapes.size())
		{
			throw runtime_error("There is no shape with such index");
		}
		return m_shapes[index];
	}
	const shared_ptr<IShape> GetShapeAtIndex(size_t index) const
	{
		if (index >= m_shapes.size())
		{
			throw runtime_error("There is no shape with such index");
		}
		return m_shapes[index];
	}

	vector<shared_ptr<IShape>>::iterator begin()
	{
		return m_shapes.begin();
	}
	vector<shared_ptr<IShape>>::const_iterator begin() const
	{
		return m_shapes.begin();
	}

	vector<shared_ptr<IShape>>::iterator end()
	{
		return m_shapes.end();
	}
	vector<shared_ptr<IShape>>::const_iterator end() const
	{
		return m_shapes.end();
	}

	void InsertShape(const shared_ptr<IShape>& shape, size_t position = numeric_limits<size_t>::max())
	{
		if (position > m_shapes.size())
		{
			m_shapes.push_back(shape);
		}
		else
		{
			m_shapes.insert(m_shapes.begin() + position, shape);
		}
	}
	void RemoveShapeAtIndex(size_t index)
	{
		if (index >= m_shapes.size())
		{
			throw runtime_error("There is no shape with such index");
		}
		m_shapes.erase(m_shapes.begin() + index);
	}

private:
	vector<shared_ptr<IShape>> m_shapes;
};
