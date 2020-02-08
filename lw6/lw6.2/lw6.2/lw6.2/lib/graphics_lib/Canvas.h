#pragma once

#include "ICanvas.h"
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

namespace graphics_lib
{
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(uint32_t rgbColor) override
		{
			ostringstream strm;
			strm << setfill('0') << setw(6) << hex << (rgbColor & 0xffffff);
			cout << "SetColor (#" << strm.str() << ')' << endl;
		}
		void MoveTo(int x, int y) override
		{
			cout << "MoveTo (" << x << ", " << y << ")" << endl;
		}
		void LineTo(int x, int y) override
		{
			cout << "LineTo (" << x << ", " << y << ")" << endl;
		}
	};
}
