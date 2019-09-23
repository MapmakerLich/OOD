#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		cout << "Current Temp " << data.temperature << endl;
		cout << "Current Hum " << data.humidity << endl;
		cout << "Current Pressure " << data.pressure << endl;
		cout << "----------------" << endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		resetData(m_minTemperature, m_maxTemperature, m_accTemperature, data.temperature, m_countAccTemp);
		resetData(m_minHumidity, m_maxHumidity, m_accHumidity, data.humidity, m_countAccPress);
		resetData(m_minPressure, m_maxPressure, m_accPressure, data.pressure, m_countAccPress);
		cout << "Temperature:" << endl;
		output(m_minTemperature, m_maxTemperature, m_accTemperature, m_countAccTemp);
		cout << "Pressure:" << endl;
		output(m_minPressure, m_maxPressure, m_accPressure, m_countAccPress);
		cout << "Humidity:" << endl;
		output(m_minHumidity, m_maxHumidity, m_accHumidity, m_countAccPress);
		cout << "----------------" << endl;
	}

	void output(double min, double max, double acc, unsigned count)
	{
		cout << "Min " << min << endl;
		cout << "Max " << max << endl;
		cout << "Average " << (acc / count) << endl;
		cout << endl;
	}

	void resetData(double& min, double& max, double& acc, double givenData, unsigned& count)
	{
		if (min > givenData)
		{
			min = givenData;
		}
		if (max < givenData)
		{
			max = givenData;
		}
		acc += givenData;
		count++;
	}

	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accTemperature = 0;
	unsigned m_countAccTemp = 0;

	double m_minHumidity = std::numeric_limits<double>::infinity();
	double m_maxHumidity = -std::numeric_limits<double>::infinity();
	double m_accHumidity = 0;
	unsigned m_countAccHum = 0;

	double m_minPressure = std::numeric_limits<double>::infinity();
	double m_maxPressure = -std::numeric_limits<double>::infinity();
	double m_accPressure = 0;
	unsigned m_countAccPress = 0;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
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
	SWeatherInfo GetChangedData()const override
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
