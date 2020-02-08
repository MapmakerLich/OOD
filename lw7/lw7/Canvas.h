#pragma once

#include "ICanvas.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class CCanvas : public ICanvas
{
public:
	CCanvas(ostream& strm = cout)
		: m_strm(strm)
		, m_fillHasBegin(false)
	{
	}
	~CCanvas()
	{
		EndFill();
	}
	void SetLineColor(RGBAColor color) override
	{
		ostringstream strm;
		strm << setfill('0') << setw(8) << hex << color;
		m_strm << "SetLineColor (#" << strm.str() << ')' << endl;
	}
	void SetLineWidth(double width)
	{
		m_strm << "SetLineWidth (" << width << ")" << endl;
	}
	void BeginFill(RGBAColor color) override
	{
		EndFill();

		ostringstream strm;
		strm << setfill('0') << setw(8) << hex << color;
		m_strm << "BeginFill (#" << strm.str() << ')' << endl;
		m_fillHasBegin = true;
	}
	void EndFill() override
	{
		if (m_fillHasBegin)
		{
			m_strm << "EndFill" << endl;
			m_fillHasBegin = false;
		}
	}
	void MoveTo(double x, double y) override
	{
		m_strm << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(double x, double y) override
	{
		m_strm << "LineTo (" << x << ", " << y << ")" << endl;
	}
	void DrawEllipse(double left, double top, double width, double height)
	{
		m_strm << "DrawEllipse (" << left << ", " << top << ", " << width << ", " << height << ")" << endl;
	}

private:
	ostream& m_strm;
	bool m_fillHasBegin;
};