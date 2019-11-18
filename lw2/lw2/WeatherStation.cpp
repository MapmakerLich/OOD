#include "WeatherData.h"
#include "WeatherDataPro.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData wd("In");
	CWeatherDataPro wd2("Out");

	CDisplay display(wd, wd2, 2);

	CStatsDisplay statsDisplay(wd, wd2, 1);

	wd.SetMeasurements(3, 0.7, 760);
	wd2.SetMeasurements(4, 0.8, 761, 92, 5);

	wd.SetMeasurements(10, 0.8, 761);
	wd2.SetMeasurements(-10, 0.8, 761, 88, 6);
	return 0;
}