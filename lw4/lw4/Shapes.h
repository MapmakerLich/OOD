#pragma once
#include "Shape.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <stdexcept>

class CRectangle : public CShape
{
public:
	CRectangle(const Point& leftTop, const Point& rightBottom, Color color = Color::Black)
		: CShape(color)
	{
		if (leftTop.x > rightBottom.x || leftTop.y < rightBottom.y)
		{
			throw std::invalid_argument("Cannot create a rectangle, invalid location of left top and right bottom vertices");
		}
		m_leftTop = leftTop;
		m_rightBottom = rightBottom;
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(GetColor());

		Point leftBottom{ m_leftTop.x, m_rightBottom.y };
		Point rightTop{ m_rightBottom.x, m_leftTop.y };

		canvas.DrawLine(m_leftTop, rightTop);
		canvas.DrawLine(rightTop, m_rightBottom);
		canvas.DrawLine(m_rightBottom, leftBottom);
		canvas.DrawLine(leftBottom, m_leftTop);
	}

	Point GetLeftTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_rightBottom;
	}

private:
	Point m_leftTop;
	Point m_rightBottom;
};

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(int8_t verticesCount, const Point& center, double radius, Color color = Color::Black)
		: CShape(color)
		, m_center(center)
	{
		if (verticesCount < 3)
		{
			throw std::invalid_argument("Cannot create a regular polygon, the number of vertices must be at least three");
		}
		if (radius < 0)
		{
			throw std::invalid_argument("Cannot create a regular polygon, the radius cannot be negative");
		}
		m_radius = radius;
		InitializeVertices(verticesCount);
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(GetColor());

		for (size_t i = 0; i < m_vertices.size(); i++)
		{
			if (i + 1 < m_vertices.size())
			{
				canvas.DrawLine(m_vertices[i], m_vertices[i + 1]);
			}
			else
			{
				canvas.DrawLine(m_vertices[i], m_vertices[0]);
			}
		}
	}

	int8_t GetVerticesCount() const
	{
		return (int8_t)m_vertices.size();
	}
	Point GetCenter() const
	{
		return m_center;
	}
	double GetRadius() const
	{
		return m_radius;
	}

private:
	Point m_center;
	double m_radius;
	std::vector<Point> m_vertices;

	void InitializeVertices(int8_t verticesCount)
	{
		double angleBetweenVertices = 2 * M_PI / verticesCount;
		for (int8_t i = 0; i < verticesCount; i++)
		{
			Point vertex;
			vertex.x = m_center.x + m_radius * sin(i * angleBetweenVertices);
			vertex.y = m_center.y - m_radius * cos(i * angleBetweenVertices);
			m_vertices.push_back(vertex);
		}
	}
};
class CTriangle : public CShape
{
public:
	CTriangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, Color color = Color::Black)
		: CShape(color)
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(GetColor());

		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

	Point GetVertex1() const
	{
		return m_vertex1;
	}
	Point GetVertex2() const
	{
		return m_vertex1;
	}
	Point GetVertex3() const
	{
		return m_vertex1;
	}

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
class CEllipse : public CShape
{
public:
	CEllipse(const Point& center, double horizontalRadius, double verticalRadius, Color color = Color::Black)
		: CShape(color)
		, m_center(center)
	{
		if (horizontalRadius < 0 || verticalRadius < 0)
		{
			throw std::invalid_argument("Cannot create a ellipse, the radius cannot be negative");
		}
		m_horizontalRadius = horizontalRadius;
		m_verticalRadius = verticalRadius;
	}


	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(GetColor());

		Point leftTop;
		leftTop.x = m_center.x - m_horizontalRadius;
		leftTop.y = m_center.y - m_verticalRadius;

		canvas.DrawEllipse(leftTop, m_horizontalRadius * 2, m_verticalRadius * 2);
	}


	Point GetCenter() const
	{
		return m_center;
	}
	double GetHorizontalRadius() const
	{
		return m_horizontalRadius;
	}
	double GetVerticalRadius() const
	{
		return m_verticalRadius;
	}

private:
	Point m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};