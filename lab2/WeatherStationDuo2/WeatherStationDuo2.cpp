#include "WeatherData.h"

int main()
{
	CWeatherData inWd;
	CWeatherData outWd;

	CStatsDisplay display(inWd, outWd);
	inWd.RegisterObserver(display, 0);
	outWd.RegisterObserver(display, 1);

	CStatsDisplay display2(inWd, outWd);
	inWd.RegisterObserver(display2, 0);

	inWd.SetMeasurements(3, 0.7, 760);
	outWd.SetMeasurements(4, 0.8, 761);

	outWd.RemoveObserver(display);

	inWd.SetMeasurements(10, 0.8, 761);
	outWd.SetMeasurements(-10, 0.8, 761);
	return 0;
}