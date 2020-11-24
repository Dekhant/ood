#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CStatsDisplay statsDisplay0;
	wd.RegisterObserver(statsDisplay0, 0);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);

	wd.SetMeasurements(3, 0.7, 760, SWindInfo{ 6, 60 });
	wd.SetMeasurements(4, 0.8, 761, SWindInfo{ 2, 90 });

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, SWindInfo{ 0.2, 270 });
	wd.SetMeasurements(-10, 0.8, 761, SWindInfo{ 4.6, 90 });
	return 0;
}