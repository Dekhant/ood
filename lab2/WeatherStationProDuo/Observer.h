#pragma once
#include <map>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T> const& observable) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
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
			iter->second->Update(data, *this);
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
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_observers;
};