#include "WeatherData.h"

int main()
{
	CWeatherData inWd;
	CWeatherDataPro outWd;

	CStatsDisplay display(inWd, outWd);
	inWd.RegisterObserver(display, 0);
	outWd.RegisterObserver(display, 1);

	CStatsDisplay display1(inWd, outWd);
	outWd.RegisterObserver(display1, 0);

	inWd.SetMeasurements(3, 0.7, 760);
	outWd.SetMeasurements(4, 0.8, 761, SWindInfo{ 6, 80 });

	outWd.RemoveObserver(display);

	inWd.SetMeasurements(10, 0.8, 761);
	outWd.SetMeasurements(-10, 0.8, 761, SWindInfo{ 2, 270 });
	return 0;
}