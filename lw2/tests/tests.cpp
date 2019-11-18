#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../lw2/CDisplay.h"
#include "../lw2/CStatsDisplay.h"
#include "../lw2/Observable.h"
#include "../lw2/Observer.h"
#include "../lw2/WeatherData.h"

using namespace std;

TEST_CASE("Check deletion")
{
	CWeatherData weatherData;
	CDisplay display(weatherData);
	CStatsDisplay statsDisplay(weatherData);
}
