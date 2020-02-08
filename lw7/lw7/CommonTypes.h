#pragma once

#include <stdint.h>
#include <stdexcept>

template<typename T>
struct Point
{
	T x;
	T y;
};

template<typename T>
struct Rect
{
public:
	Rect(const Point<T>& leftTop = { 0, 0 }, const T& width = 0, const T& height = 0)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
		if (m_width <= 0 || m_height <= 0)
		{
			throw std::invalid_argument("Width and height must be greater than zero");
		}
	}

	Point<T> GetLeftTop() const
	{
		return m_leftTop;
	}

	T GetWidth() const
	{
		return m_width;
	}

	T GetHeight() const
	{
		return m_height;
	}

private:
	Point<T> m_leftTop;
	T m_width;
	T m_height;
};

using PointD = Point<double>;
using RectD = Rect<double>;
using RGBAColor = uint32_t;
