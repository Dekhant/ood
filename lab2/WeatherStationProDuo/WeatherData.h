#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <optional>
#include <string>

struct SWindInfo
{
	double speed = 0;
	double direction = 0;
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	SWindInfo wind;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature() const
	{
		return m_temperature;
	}
	double GetHumidity() const
	{
		return m_humidity;
	}
	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class CWeatherDataPro : public CWeatherData
{
public:
	SWindInfo GetWindInfo() const
	{
		return m_windInfo;
	}

	void SetMeasurements(double temp, double humidity, double pressure, SWindInfo wind)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windInfo = wind;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind = GetWindInfo();
		return info;
	}

private:
	SWindInfo m_windInfo;
};

class CStatistic
{
public:
	void Update(double value)
	{
		m_min = std::min(m_min, value);
		m_max = std::max(m_max, value);
		m_acc += value;
		++m_countAcc;
	}

	std::string ToString()
	{
		return "\tmin: " + std::to_string(m_min) + "\n\tmax: " + std::to_string(m_max) + "\n\taverage: " + std::to_string(m_acc / m_countAcc);
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

#define PI 3.14159265359

class CDirectionStatistic
{
public:
	void Update(double value)
	{
		m_sinSum += sin(ToRadians(value));
		m_cosSum += cos(ToRadians(value));
	}

	std::string ToString()
	{
		double x = ToDegrees(atan2(m_sinSum, m_cosSum)) + 360;
		double average = x - trunc(x / 360) * 360;
		return "\taverage direction: " + std::to_string(average);
	}

private:
	static double ToDegrees(double value)
	{
		return value * 180 / PI;
	}

	static double ToRadians(double value)
	{
		return value * PI / 180;
	}

	double m_sinSum = 0;
	double m_cosSum = 0;
};

class CWeatherStatistics
{
public:
	void UpdateStatistics(SWeatherInfo const& data)
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);
	}
	void PrintStatistics()
	{
		std::cout << "Temperature\n"
			<< m_temperatureStats.ToString() << std::endl;
		std::cout << "Humidity\n"
			<< m_humidityStats.ToString() << std::endl;
		std::cout << "Pressure\n"
			<< m_pressureStats.ToString() << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	CStatistic m_temperatureStats;
	CStatistic m_humidityStats;
	CStatistic m_pressureStats;
};

class CWeatherStatisticsPro
{
public:
	void UpdateStatistics(SWeatherInfo const& data)
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);
		m_windSpeedStats.Update(data.wind.speed);
		m_windDirectionStats.Update(data.wind.direction);
	}
	void PrintStatistics()
	{
		std::cout << "Temperature\n"
			<< m_temperatureStats.ToString() << std::endl;
		std::cout << "Humidity\n"
			<< m_humidityStats.ToString() << std::endl;
		std::cout << "Pressure\n"
			<< m_pressureStats.ToString() << std::endl;
		std::cout << "Wind\n"
			<< m_windSpeedStats.ToString() << std::endl;
		std::cout << m_windDirectionStats.ToString() << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	CStatistic m_temperatureStats;
	CStatistic m_humidityStats;
	CStatistic m_pressureStats;
	CStatistic m_windSpeedStats;
	CDirectionStatistic m_windDirectionStats;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(CWeatherData const& inObservable, CWeatherDataPro const& outObservable)
		: m_inObservable(inObservable)
		, m_outObservable(outObservable)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_inObservable)
		{
			m_inStats.UpdateStatistics(data);

			std::cout << "Statistics indoor:\n";
			m_inStats.PrintStatistics();
		}
		if (&observable == &m_outObservable)
		{
			m_outStats.UpdateStatistics(data);

			std::cout << "Statistics outdoor:\n";
			m_outStats.PrintStatistics();
		}
	}

	CWeatherStatistics m_inStats;
	CWeatherStatisticsPro m_outStats;

	const CWeatherData& m_inObservable;
	const CWeatherData& m_outObservable;
};
