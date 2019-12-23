#pragma once

#include "ICanvas.h"
#include <string>

using namespace std;

class CCanvas : public ICanvas
{
public:
	void SetColor(Color color)
	{
		m_color = color;
	}
	void DrawLine(const Point& from, const Point& to)
	{
		cout << ColorToString() << " line from (" << from.x << ", " << from.y << ") to (" << to.x << ", " << to.y << ")\n";
	}

	void DrawEllipse(const Point& leftTop, double width, double height)
	{
		cout << ColorToString() << " ellipse with: left top point: (" << leftTop.x << ", " << leftTop.y << "); width: "
			<< width << "; height: " << height << endl;
	}

private:
	Color m_color = Color::Black;

	std::string ColorToString() const
	{
		switch (m_color)
		{
		case Color::Green:
			return "Green";

		case Color::Red:
			return "Red";

		case Color::Blue:
			return "Blue";

		case Color::Yellow:
			return "Yellow";

		case Color::Pink:
			return "Pink";

		default:
			return "Black";
		}
	}
};