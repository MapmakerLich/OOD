#pragma once

#include "Observer.h"
#include "../../catch2/catch.hpp"
#include <map>
#include <list>

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, int priority) override
	{
		m_observers.remove(&observer);
		m_priorities[&observer] = priority;
		auto i = m_observers.begin();
		for (;i != m_observers.end();i++)
		{
			if (m_priorities[*i] < priority)
			{
				m_observers.insert(i, &observer);
				break;
			}
		}
		if (i == m_observers.end())
		{
			m_observers.push_back(&observer);
		}
	}
	void NotifyObservers() override
	{
		if (m_removableObservers.size() != 0)
		{
			for (auto & observer : m_removableObservers)
			{
				m_observers.remove(observer);
				m_priorities.erase(observer);
			}
			m_removableObservers.clear();
		}
		T data = GetChangedData();
		for (auto & observer : m_observers)
		{
			observer->Update(data, m_name);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		m_removableObservers.push_back(&observer);
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;
	std::string m_name;
private:
	std::map<ObserverType *, int> m_priorities;
	std::list<ObserverType *> m_observers;
	std::list<ObserverType *> m_removableObservers;
};