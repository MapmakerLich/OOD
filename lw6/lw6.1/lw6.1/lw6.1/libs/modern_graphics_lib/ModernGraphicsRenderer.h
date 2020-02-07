#include "Point.h"
#include "RGBAColor.h"
#include <iostream>

using namespace std;

namespace modern_graphics_lib
{
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(ostream& strm)
			: m_out(strm)
		{
		}
		~CModernGraphicsRenderer()
		{
			if (m_drawing)
			{
				EndDraw();
			}
		}

		void BeginDraw()
		{
			if (m_drawing)
			{
				throw logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << endl;
			m_drawing = true;
		}
		void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
		{
			if (!m_drawing)
			{
				throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}
			m_out << "  <line fromX=\"" << start.x << "\" fromY=\"" << start.y
				<< "\" toX=\"" << end.x << "\" toY=\"" << end.y << "\">\n";
			m_out << "    <color r=\"" << color.r << "\" g=\"" << color.g
				<< "\" b=\"" << color.b << "\" a=\"" << color.a << "\"/>\n";
			m_out << "  </line>\n";
		}
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << endl;
			m_drawing = false;
		}

	private:
		std::ostream& m_out;
		bool m_drawing = false;
	};
}