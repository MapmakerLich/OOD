#pragma once

#include "Shape.h"
#include <memory>
#include <vector>

class CPictureDraft
{
public:
	CPictureDraft() = default;
	CPictureDraft(const CPictureDraft&) = delete;
	CPictureDraft(CPictureDraft&&) = default;

	CPictureDraft& operator=(const CPictureDraft&) = delete;
	CPictureDraft& operator=(CPictureDraft&&) = default;

	const CShape& operator[](size_t index) const
	{
		if (index >= m_shapes.size())
		{
			throw std::runtime_error("There is no shape with this index");
		}
		return *(m_shapes[index]);
	}


	bool IsEmpty() const
	{
		return m_shapes.empty();
	}
	size_t GetShapesCount() const
	{
		return m_shapes.size();
	}
	void AddShape(std::unique_ptr<CShape>&& shape)
	{
		m_shapes.push_back(move(shape));
	}

private:
	std::vector<std::unique_ptr<CShape>> m_shapes;
};
