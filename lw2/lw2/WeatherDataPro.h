#pragma once
#include "WeatherData.h"

struct SWeatherInfoPro : public SWeatherInfo
{

};

class CWeatherDataPro : public CObservable<SWeatherInfoPro>
{
public:
	CWeatherDataPro(string str)
	{
		m_name = str;
	}
	double GetDir() const
	{
		return m_dir;
	}
	double GetSpeed() const
	{
		return m_speed;
	}
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
	void SetMeasurements(double temp, double humidity, double pressure, double dir, double speed) 
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_dir = dir;
		m_speed = speed;

		MeasurementsChanged();
	}
protected:
	SWeatherInfoPro GetChangedData()const override
	{
		SWeatherInfoPro info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.dir = GetDir();
		info.speed = GetSpeed();
		return info;
	}
private:
	double m_dir = 0.0;
	double m_speed = 0.0;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
