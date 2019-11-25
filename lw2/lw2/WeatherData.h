#pragma once
//#include "CStatsDisplay.h"
#include "Observable.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(string str)
	{
		m_name = str;
	}

	// ����������� � �������� �������
	double GetTemperature()const
	{
		return m_temperature;
	}
	// ������������� ��������� (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// ����������� �������� (� ��.��.��)
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
