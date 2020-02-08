#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../lw6.2/GraphicsAdapter.h"
#include <sstream>

using namespace std;
using namespace app;
using namespace modern_graphics_lib;

TEST_CASE("Draw line from default start position")
{
	ostringstream outStrm;
	CGraphicsAdapter adapter(outStrm);

	adapter.BeginDraw();
	adapter.LineTo(10, 15);
	adapter.EndDraw();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	CHECK(str == "<draw>");
	getline(result, str);
	CHECK(str == "  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"15\">");
	getline(result, str);
	CHECK(str == "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>");
	getline(result, str);
	CHECK(str == "  </line>");
	getline(result, str);
	CHECK(str == "</draw>");

	CHECK_FALSE(getline(result, str));
}

TEST_CASE("Adapter set color, move to and line to tests")
{
	ostringstream outStrm;
	CGraphicsAdapter adapter(outStrm);

	adapter.BeginDraw();
	adapter.SetColor(0x00ff00ff);
	adapter.MoveTo(20, 25);
	adapter.LineTo(30, 35);
	adapter.EndDraw();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	CHECK(str == "<draw>");
	getline(result, str);
	CHECK(str == "  <line fromX=\"20\" fromY=\"25\" toX=\"30\" toY=\"35\">");
	getline(result, str);
	CHECK(str == "    <color r=\"1\" g=\"0\" b=\"1\" a=\"0\"/>");
	getline(result, str);
	CHECK(str == "  </line>");
	getline(result, str);
	CHECK(str == "</draw>");

	CHECK_FALSE(getline(result, str));
}

TEST_CASE("Adapter twice line to tests")
{
	ostringstream outStrm;
	CGraphicsAdapter adapter(outStrm);

	adapter.BeginDraw();
	adapter.SetColor(0xff00ff00);
	adapter.LineTo(30, 35);
	adapter.LineTo(40, 45);
	adapter.EndDraw();

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	CHECK(str == "<draw>");
	getline(result, str);
	CHECK(str == "  <line fromX=\"0\" fromY=\"0\" toX=\"30\" toY=\"35\">");
	getline(result, str);
	CHECK(str == "    <color r=\"0\" g=\"1\" b=\"0\" a=\"1\"/>");
	getline(result, str);
	CHECK(str == "  </line>");
	getline(result, str);
	CHECK(str == "  <line fromX=\"30\" fromY=\"35\" toX=\"40\" toY=\"45\">");
	getline(result, str);
	CHECK(str == "    <color r=\"0\" g=\"1\" b=\"0\" a=\"1\"/>");
	getline(result, str);
	CHECK(str == "  </line>");
	getline(result, str);
	CHECK(str == "</draw>");

	CHECK_FALSE(getline(result, str));
}