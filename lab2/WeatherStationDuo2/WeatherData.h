#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
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

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
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

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(CWeatherData const& inObservable, CWeatherData const& outObservable)
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
	CWeatherStatistics m_outStats;

	const CWeatherData& m_inObservable;
	const CWeatherData& m_outObservable;
};