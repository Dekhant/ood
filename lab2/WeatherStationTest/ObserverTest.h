#pragma once
#include "../WeatherStation/Observer.h"
#include "../WeatherStation//WeatherData.h"
#include <iostream>

template <class T>
class CObservableTest : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, unsigned priority) override
	{
		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		std::multimap<int, ObserverType*> observers = m_observers;

		for (auto iter = observers.rbegin(); iter != observers.rend(); ++iter)
		{
			iter->second->Update(data);
			iter->second->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto iter = m_observers.begin(); iter != m_observers.end(); ++iter)
		{
			if (iter->second == &observer)
			{
				m_observers.erase(iter);
				break;
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_observers;
};


class CWeatherDataTest : public CObservableTest<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
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


typedef IObservable<SWeatherInfo> ObservableType;

class CRemovedObserver : public IObserver<SWeatherInfo>
{
public:
	CRemovedObserver(ObservableType& observable)
	{
		m_observable = &observable;
	}

private:
	void Update(SWeatherInfo const& data)
	{
		m_observable->RemoveObserver(*this);

		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	ObservableType* m_observable;
};


class CPriorityObserver : public IObserver<SWeatherInfo>
{
public:
	CPriorityObserver(int id, std::ostream& out)
		: m_myId(id)
		, m_out(out)
	{
	}

private:
	void Update(SWeatherInfo const& data)
	{
		m_out << m_myId;
	}

	int m_myId;
	std::ostream& m_out;
};