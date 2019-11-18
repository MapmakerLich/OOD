#include "CStatsDisplay.h"
#include "WeatherData.h"

CStatsDisplay::CStatsDisplay(IObservable<SWeatherInfo> &data1, IObservable<SWeatherInfoPro> &data2, int priority)
	:m_data1(&data1),
	m_data2(&data2)
{
	SetZero(m_minTemperature, m_maxTemperature, m_accTemperature, m_countAccTemp);
	SetZero(m_minPressure, m_maxPressure, m_accPressure, m_countAccPress);
	SetZero(m_minHumidity, m_maxHumidity, m_accHumidity, m_countAccHum);
	SetZero(m_minDir, m_maxDir, m_accDir, m_countAccDir);
	SetZero(m_minSpeed, m_maxSpeed, m_accSpeed, m_countAccSpeed);
	m_data1->RegisterObserver(*this, priority);
	m_data2->RegisterObserver(*this, priority);
}

void CStatsDisplay::RemoveObservers()
{
	m_data2->RemoveObserver(*this);
	m_data1->RemoveObserver(*this);
}

void CStatsDisplay::Update(SWeatherInfo const& data, string str)
{
	RemoveObservers();
	ChangeData(m_minTemperature, m_maxTemperature, m_accTemperature, data.temperature, m_countAccTemp);
	ChangeData(m_minPressure, m_maxPressure, m_accPressure, data.pressure, m_countAccPress);
	ChangeData(m_minHumidity, m_maxHumidity, m_accHumidity, data.humidity, m_countAccHum);
	cout << str + " Temperature:" << endl;
	Output(m_minTemperature, m_maxTemperature, m_accTemperature, m_countAccTemp, str);
	cout << str + " Pressure:" << endl;
	Output(m_minPressure, m_maxPressure, m_accPressure, m_countAccPress, str);
	cout << str + " Humidity:" << endl;
	Output(m_minHumidity, m_maxHumidity, m_accHumidity, m_countAccHum, str);
	cout << "----------------" << endl;
}

void CStatsDisplay::Update(SWeatherInfoPro const& data, string str)
{
	RemoveObservers();
	ChangeData(m_minTemperature, m_maxTemperature, m_accTemperature, data.temperature, m_countAccTemp);
	ChangeData(m_minPressure, m_maxPressure, m_accPressure, data.pressure, m_countAccPress);
	ChangeData(m_minHumidity, m_maxHumidity, m_accHumidity, data.humidity, m_countAccHum);
	ChangeData(m_minDir, m_maxDir, m_accDir, data.dir, m_countAccDir);
	ChangeData(m_minSpeed, m_maxSpeed, m_accSpeed, data.speed, m_countAccSpeed);
	cout << str + " Temperature:" << endl;
	Output(m_minTemperature, m_maxTemperature, m_accTemperature, m_countAccTemp, str);
	cout << str + " Pressure:" << endl;
	Output(m_minPressure, m_maxPressure, m_accPressure, m_countAccPress, str);
	cout << str + " Humidity:" << endl;
	Output(m_minHumidity, m_maxHumidity, m_accHumidity, m_countAccHum, str);
	cout << str + " Speed: " << endl;
	Output(m_minSpeed, m_maxSpeed, m_accSpeed, m_countAccSpeed, str);
	cout << str + " Direction: " << endl;
	Output(m_minDir, m_maxDir, m_accDir, m_countAccDir, str);
	cout << "----------------" << endl;
}

void CStatsDisplay::Output(double min, double max, double acc, int count, string str)
{
	cout << str + " Min " << min << endl;
	cout << str + " Max " << max << endl;
	cout << str + " Average " << (acc / count) << endl;
	cout << endl;
}

void CStatsDisplay::ChangeData(double& min, double& max, double& acc, double givenData, int& count)
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
	++count;
}

void CStatsDisplay::SetZero(double& min, double& max, double& acc, int& count)
{
	min = numeric_limits<double>::infinity();
	max = -numeric_limits<double>::infinity();
	acc = 0;
	count = 0;
}