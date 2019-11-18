#pragma once
#include "CDisplay.h"

class CStatsDisplay : public IObserver<SWeatherInfo>, public IObserver<SWeatherInfoPro>
{
public:
	CStatsDisplay(IObservable<SWeatherInfo> &data1, IObservable<SWeatherInfoPro> &data2, int priority);
private:
	IObservable<SWeatherInfo>* m_data1;
	IObservable<SWeatherInfoPro>* m_data2;

	void Update(SWeatherInfo const& data, string str) override;
	void Update(SWeatherInfoPro const& data, string str) override;

	void Output(double min, double max, double acc, int count, string str);

	void ChangeData(double& min, double& max, double& acc, double givenData, int& count);

	void SetZero(double& min, double& max, double& acc, int& count);

	void RemoveObservers();

	double m_minTemperature;
	double m_maxTemperature;
	double m_accTemperature;
	int m_countAccTemp;

	double m_minHumidity;
	double m_maxHumidity;
	double m_accHumidity;
	int m_countAccHum;

	double m_minPressure;
	double m_maxPressure;
	double m_accPressure;
	int m_countAccPress;

	double m_minDir;
	double m_maxDir;
	double m_accDir;
	int m_countAccDir;

	double m_minSpeed;
	double m_maxSpeed;
	double m_accSpeed;
	int m_countAccSpeed;
};
