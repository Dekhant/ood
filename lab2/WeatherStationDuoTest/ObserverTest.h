#pragma once
#include "../WeatherStationDuo/WeatherData.h"

class CWeatherStatisticsTest
{
public:
	void UpdateStatistics(SWeatherInfo const& data)
	{
		m_temperetureStats.Update(data.temperature);
	}
	void PrintStatistics(std::ostream& out)
	{
		out << m_temperetureStats.ToString();
	}
private:
	CStatistic m_temperetureStats;
};

class CStatsDisplayTest : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplayTest(CWeatherData const& inObservable, CWeatherData const& outObservable, std::ostream& out)
		: m_inObservable(inObservable)
		, m_outObservable(outObservable)
		, m_out(out)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_inObservable)
		{
			m_inStats.UpdateStatistics(data);

			m_out << "in ";
			m_inStats.PrintStatistics(m_out);
		}
		if (&observable == &m_outObservable)
		{
			m_outStats.UpdateStatistics(data);

			m_out << "out ";
			m_outStats.PrintStatistics(m_out);
		}
	}

	CWeatherStatisticsTest m_inStats;
	CWeatherStatisticsTest m_outStats;

	const CWeatherData& m_inObservable;
	const CWeatherData& m_outObservable;

	std::ostream& m_out;
};